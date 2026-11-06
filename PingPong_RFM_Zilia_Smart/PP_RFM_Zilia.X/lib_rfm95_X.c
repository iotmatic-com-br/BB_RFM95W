///////////////////////////////////////////////////////////////////////
////        Biblioteca SPI por software -  RFM95 - Mplab X
////                                               11/06/2026
////                                               REVISÃO   03/11/2026
///////////////////////////////////////////////////////////////////////
////		usar antes do main:    	#include "lib_rfm95_X.c"
///////////////////////////////////////////////////////////////////////

//@@@@@@@@@@@@@@@@@@@@@@@@ Ajustar aqui os pinos de I/O 
//______saidas I/O
#define CSN1on      CSN_SetLow()    // AJUSTAR DE ACORDO COM		   		
#define CSN1off     CSN_SetHigh()   // O PROJETO !
#define CLK0   		SCK_SetLow()				
#define CLK1   		SCK_SetHigh()	  		
#define MOSI0   	MOSI_SetLow()				
#define MOSI1   	MOSI_SetHigh()	  		
#define RstRFM   	RSTRFM_SetLow()				
#define RunRFM   	RSTRFM_SetHigh()	  		
//______entradas I/O
#define MISO_1      (MISO_GetValue())==1     	
#define DIO0_1      (DIO0_GetValue())==1     	
#define DIO0_0      (DIO0_GetValue())==0     	

//uint8_t _swSPI_write(uint8_t dataout);
//uint8_t _swSPI_read(void);

//// Vars
uint8_t RFM_IRQ_flags;
uint8_t RFM_numBytesRec;
uint8_t RFM_RX_buffer[6];
uint8_t RFM_numBytesTx;
uint8_t RFM_TX_buffer[6];

////////////////////////////////////////////////////////////////////////
uint8_t _swSPI_write(uint8_t dataout)			// envia 8 bits pelo spi por sw
{
uint8_t bit_ctr,dataRead;    
	dataRead=0;
    for(bit_ctr=0;bit_ctr<8;bit_ctr++)      // output 8-bit
    {
		if(dataout & 0x80) MOSI1;
        else               MOSI0;
        dataout = (uint8_t)(dataout << 1);           // shift next bit into MSB..
        CLK1; 
        CLK0; 
	}
    return (dataRead);
}		  
////////////////////////////////////////////////////////////////////////
uint8_t _swSPI_read()			// faz o 'read' do spi via sw
{
uint8_t bit_ctr,datarec;
	datarec=0;
    for(bit_ctr=0;bit_ctr<8;bit_ctr++)      // output 8-bit clocks
    {
        datarec = (uint8_t)(datarec << 1);           // shift next bit into MSB..        //        (uint8_t)datarec = (uint8_t)(datarec << 1);           // shift next bit into MSB..
        CLK1;
        if(MISO_1) datarec |= 1;
		CLK0;         	  
    }
    return (datarec);
}		  
////////////////////////////////////////////////////////////////////////
//// RFM routines
////////////////////////////////////////////////////////////////////////
// -------------------- Low-Level RFM95 SPI Primitives -----------------
void RFM95_WriteRegister(uint8_t reg, uint8_t value) 
{
    CSN1on;
    _swSPI_write(reg | 0x80);       // MSB = 1 for Write operations
    _swSPI_write(value);
    CSN1off;
}
uint8_t RFM95_ReadRegister(uint8_t reg) 
{
uint8_t value;
    CSN1on;
    _swSPI_write(reg & 0x7F);       // MSB = 0 for Read operations
    value = _swSPI_read();          // Send dummy byte to clock data in
    CSN1off;
    return value;
}
// -------------------- RFM95 FiFo SPI Functions -----------------
void RFM95_WriteFIFO(uint8_t *data, uint8_t length) 
{
    CSN1on;
    _swSPI_write(0x00 | 0x80); // RegFifo (0x00) with Write Bit (0x80)
    for (uint8_t i = 0; i < length; i++) 
    {
        _swSPI_write(data[i]);
    }
    CSN1off;
}
void RFM95_ReadFIFO(uint8_t *buffer, uint8_t length) 
{
    CSN1on;
    _swSPI_write(0x00 & 0x7F);  // RegFifo (0x00) com bit de leitura (MSB = 0)
    for (uint8_t i = 0; i < length; i++) 
    {
        buffer[i] = _swSPI_read(); // Clock para ler os dados
    }
    CSN1off;
}
// -------------------- RFM95 Modo RX -----------------
void RFM95__ModoRX()
{
    // 1. Se o rádio não estiver em modo RX Contínuo, força ele a entrar
    if ((RFM95_ReadRegister(0x01) & 0x07) != 0x05) 
    {
        RFM95_WriteRegister(0x01, 0x85); // LoRa + RX Contínuo
    }
}
// -------------------- RFM95 LoRa RX Configurations Sequence ------------
void RFM95_Init_RX_9063(void) 
{
    // 1. Força modo Sleep para configurar LoRa
    RFM95_WriteRegister(0x01, 0x00); 
    RFM95_WriteRegister(0x01, 0x80); // LoRa + Sleep
    
    // 2. Frequência 906.3 MHz
    RFM95_WriteRegister(0x06, 0xE2); 
    RFM95_WriteRegister(0x07, 0x92); 
    RFM95_WriteRegister(0x08, 0x33); 

    // 3. Modem: BW 125kHz, CR 4/8
    RFM95_WriteRegister(0x1D, 0x78); 

    // 4. Modem: SF12, CRC On
    RFM95_WriteRegister(0x1E, 0xC4); 

    // 5. Low Data Rate Optimize (Obrigatório para SF12)
    RFM95_WriteRegister(0x26, 0x08); 
    
    // 6. Sync Word (O mesmo que fez funcionar o TX com a Zilia!)
    RFM95_WriteRegister(0x39, 0x34); 

    // 7. Configura o ponteiro base de RX no FIFO para o início (0x00)
    RFM95_WriteRegister(0x0F, 0x00); // RegFifoRxBaseAddr
    
    // 8. Garante DIO0 mapeado para RxDone em modo RX
    RFM95_WriteRegister(0x40, 0x00); 
}
// -------------------- RFM95 LoRa TX Configurations Sequence ------------
void RFM95_Init_TX_9063(void) 
{
    // 1. Force Sleep Mode to allow switching into LoRa mode
    RFM95_WriteRegister(0x01, 0x00); // RegOpMode -> Sleep (0x00)
    
    // 2. Enable LoRa Mode (Bit 7 = 1) while remaining in Sleep
    RFM95_WriteRegister(0x01, 0x80); // RegOpMode -> LoRa + Sleep
    
    // 3. Set RF Carrier Frequency to 906.3 MHz
    // Calculation: 906,300,000 / 61.035156 = 14,848,819 (0xE29233)
    RFM95_WriteRegister(0x06, 0xE2); // RegFrfMsb
    RFM95_WriteRegister(0x07, 0x92); // RegFrfMid
    RFM95_WriteRegister(0x08, 0x33); // RegFrfLsb

    // 4. Configure Modem: BW = 125 kHz (0x70), Coding Rate = 4/8 (0x08), Explicit Header (0x00)
    RFM95_WriteRegister(0x1D, 0x78); // RegModemConfig1

    // 5. Configure Modem: Spreading Factor = SF12 (0xC0), CRC = On (0x04)
    RFM95_WriteRegister(0x1E, 0xC4); // RegModemConfig2

    // 6. Low Data Rate Optimize (Mandatory for SF12 @ 125kHz)
    RFM95_WriteRegister(0x26, 0x08); // RegModemConfig3 -> LowDataRateOptimize = 1
    
    // 7. Power Setup: Max Power via PA_BOOST
    RFM95_WriteRegister(0x09, 0xFF); // RegPaConfig -> PA_BOOST + Max output
    RFM95_WriteRegister(0x4D, 0x87); // RegPaDac -> Enables +20dBm true max power
    
    // Altera o Sync Word no RFM95 para 0x34 (padrão de redes públicas/Zilia)
    RFM95_WriteRegister(0x39, 0x34);
}

// --- Transmission Sequence Routine ---
/// preciso do 'RFM_numBytesTx' ajustado e do 'RFM_TX_buffer[]' preenchido]
void RFM95_Transmit(uint8_t modo) 
{
    // 1. Put module into Standby mode to ready the FIFO
    RFM95_WriteRegister(0x01, 0x81); // RegOpMode -> LoRa + Standby

    // 2. Clear old internal FIFO pointers
    RFM95_WriteRegister(0x0E, 0x00); // RegFifoTxBaseAddr -> 0x00
    RFM95_WriteRegister(0x0D, 0x00); // RegFifoAddrPtr -> 0x00

    // 3. Stream payload directly into the FIFO register
    RFM95_WriteFIFO(RFM_TX_buffer, RFM_numBytesTx);

    // 4. Declare payload size to the packet engine
    RFM95_WriteRegister(0x22, RFM_numBytesTx); // RegPayloadLength

    // 5. Clear all stale interrupt flags
    RFM95_WriteRegister(0x12, 0xFF); // RegIrqFlags

    // 6. Begin Transmit Mode
    RFM95_WriteRegister(0x01, 0x83); // RegOpMode -> LoRa + TX Mode

    // 7. Wait for complete transmission (TxDone Flag)
    // At SF12, aprox. 700-800 milliseconds!
    switch (modo)
    {
        case 0:          //delay
            __delay_ms(1000);
            break;
        case 1:          //pooling
            while (1) 
            {
                RFM_IRQ_flags = RFM95_ReadRegister(0x12); // Read RegIrqFlags
                if (RFM_IRQ_flags & 0x08)                         // Check Bit 3 (TxDone)
                    break; 
            }
            break;
        case 2:          //DIO0
            
            break;
        default:         //delay
            break;
        
    }

    // 8. Clean up: Clear the TxDone flag and put radio back into Standby
    RFM95_WriteRegister(0x12, 0x08); // Write 1 to clear TxDone bit
    RFM95_WriteRegister(0x01, 0x81); // Return to Standby mode
}

// --- Rotina de Escuta (Loop ou Polling) ---
// Retorna o número de bytes recebidos, ou 0 se não recebeu nada ainda.
            //uint8_t RFM95_Check_For_Packet(uint8_t *rx_buffer, uint8_t max_len) 
            //{
            //    // Se o rádio não estiver em modo RX Contínuo, força ele a entrar
            //    // Bit 2-0 = 101 (0x05) -> Modo RXCONTINUOUS
            //    if ((RFM95_ReadRegister(0x01) & 0x07) != 0x05) 
            //    {
            //        RFM95_WriteRegister(0x01, 0x85); // LoRa + RX Contínuo
            //    }
            //
            //    // Lê as interrupções registradas no rádio
            //    RFM_IRQ_flags = RFM95_ReadRegister(0x12); // RegIrqFlags
            //
            //    // Verifica Bit 6 (RxDone) -> Pacote recebido com sucesso!
            //    if (RFM_IRQ_flags & 0x40) 
            //    {
            //        // Opcional: Verifica Bit 5 (PayloadCrcError) para ver se o pacote veio corrompido
            //        if (RFM_IRQ_flags & 0x20) 
            //        {
            //            // Erro de CRC! Limpa as flags e ignora o pacote corrompido
            //            RFM95_WriteRegister(0x12, 0xFF); 
            //            return 0; 
            //        }
            //
            //        // Descobre quantos bytes foram recebidos de fato
            //        uint8_t bytes_received = RFM95_ReadRegister(0x13); // RegRxNbBytes
            //
            //        // Descobre onde o rádio guardou o último pacote dentro do FIFO interno
            //        uint8_t fifo_packet_addr = RFM95_ReadRegister(0x10); // RegFifoRxCurrentAddr
            //
            //        // Aponta o ponteiro de leitura do SPI para esse endereço correto do FIFO
            //        RFM95_WriteRegister(0x0D, fifo_packet_addr); // RegFifoAddrPtr
            //
            //        // Proteção para não estourar o seu buffer de destino
            //        if (bytes_received > max_len) 
            //        {
            //            bytes_received = max_len;
            //        }
            //
            //        // Lê os dados do FIFO para o seu buffer na RAM do microcontrolador
            //        RFM95_ReadFIFO(rx_buffer, bytes_received);
            //
            //        // Limpa as flags de interrupção escrevendo 1 nelas (especialmente RxDone)
            //        RFM95_WriteRegister(0x12, 0xFF); 
            //
            //        return bytes_received; // Retorna a quantidade de bytes válidos no buffer
            //    }
            //    return 0; // Nenhum pacote recebido ainda
            //}

// --- Rotina Polling) DIO0
// Retorna o número de bytes recebidos, ou 0 se não recebeu nada ainda.
uint8_t RFM95_Check_For_Packet_DIO0(uint8_t *rx_buffer, uint8_t max_len) 
{   
//    // 1. Se o rádio não estiver em modo RX Contínuo, força ele a entrar
//    if ((RFM95_ReadRegister(0x01) & 0x07) != 0x05) 
//    {
//        RFM95_WriteRegister(0x01, 0x85); // LoRa + RX Contínuo
//    }

    // 2. Faz o polling do PINO FÍSICO DIO0 ao invés do SPI
    if (DIO0_1)  // Mudou para HIGH? Temos um pacote!
    {    
        // Embora o DIO0 suba, ainda precisamos ler o RegIrqFlags uma vez 
        // para checar se o pacote não veio com erro de CRC.
        RFM_IRQ_flags = RFM95_ReadRegister(0x12);

        if (RFM_IRQ_flags & 0x20)  // PayloadCrcError detetado
        {    
            RFM95_WriteRegister(0x12, 0xFF); // Limpa as flags no rádio
            // O pino DIO0 cai para LOW automaticamente quando limpamos as flags
            return 99; 
        }

        // 3. Processo normal de leitura do FIFO (igual ao anterior)
        uint8_t bytes_received = RFM95_ReadRegister(0x13); // RegRxNbBytes
        uint8_t fifo_packet_addr = RFM95_ReadRegister(0x10); // RegFifoRxCurrentAddr
        
        RFM95_WriteRegister(0x0D, fifo_packet_addr); // Aponta ponteiro SPI

        if (bytes_received > max_len) 
        {
            bytes_received = max_len;
        }

        RFM95_ReadFIFO(rx_buffer, bytes_received); // Puxa os dados

        // 4. LIMPEZA CRUCIAL: Limpa as flags escrevendo 0xFF no RegIrqFlags.
        // Isso fará o chip RFM95 derrubar o pino DIO0 de volta para LOW (0),
        // deixando-o pronto para o próximo pacote da Zilia.
        RFM95_WriteRegister(0x12, 0xFF); 

        return bytes_received;
    }

    return 0; // Nenhum pacote no ar ainda
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//