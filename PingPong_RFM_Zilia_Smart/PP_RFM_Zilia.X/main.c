/***********************************************************************
 *      #####    PING PONG DE VALIDAÇÃO    #####
 *      BB_RFM95W    <-->   Zilia (Smart Modular)
 * 
 *      Comunicacao LoRa P2P entre RFM95W e Módulo Lora Zilia )Smart Modular)
 *      Frequencia: 906.300.000 Hz
 * 
 *  - PIC pisca o led verde e envia PING.
 *  - Se receber PONG, pisca o vermelho (timeout 5s)
 * 
 *                                                          10/11/2026
**********************************************************************  */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning disable 520
#include "mcc_generated_files/system/system.h"
#pragma config LVP = ON  

////////////////////////////////////////////////////////////////////////////
///// External LIbs
#include "lib_rfm95_X.c"

////////////////////////////////////////////////////////////////////////////////
//// Macros
#define     bp      __nop()

#define     vmon        VM_SetLow()        
#define     vmoff       VM_SetHigh()        
#define     vmtg        VM_Toggle()        
#define     vdon        VD_SetLow()        
#define     vdoff       VD_SetHigh()        
#define     vdtg        VD_Toggle() 

////////////////////////////////////////////////////////////////////////////
///// VARS
uint8_t     fOK,data;

////////////////////////////////////////////////////////////////////////////
///// ROTINAS

////////////////////////////////////////////////////////////////////////////
///// Main application
int main(void)
{
    SYSTEM_Initialize();
    vdoff;
    vmoff;

    while(1)
    {
        //--------------   Envia PING
        __nop();
        vdon;
        RFM95_Init_TX_9063();
        __nop();
        
        // Garantir 'RFM_numBytesTx' ajustado e do 'RFM_TX_buffer[]' preenchido
        RFM_TX_buffer[0]='P';
        RFM_TX_buffer[1]='I';
        RFM_TX_buffer[2]='N';
        RFM_TX_buffer[3]='G';
        RFM_TX_buffer[4]= 0x0D;
        RFM_numBytesTx=5;
                
        RFM95_Transmit(1);      // modo delay 1,5s
        vdoff;

        //----------------  ciclo de espera do PONG +- 10s
        RFM95_Init_RX_9063();
        RFM95__ModoRX();
        
        for (uint8_t ciclo=0; ciclo<100; ciclo++)
        {
            vdon;
            __delay_ms(25);
            vdoff;
            __delay_ms(25);

            __nop();
            if (DIO0_1)
            {
                __nop();
                // Passa o buffer e o tamanho máximo dele
                RFM_numBytesRec = RFM95_Check_For_Packet_DIO0(RFM_RX_buffer, 64);
                if (RFM_numBytesRec > 98) 
                {
                    vmon;
                    __delay_ms(100);
                    vmoff;
                }
                else if (RFM_numBytesRec > 0) 
                {
                    __nop();
                    RFM_numBytesRec--;
                    RFM_RX_buffer[RFM_numBytesRec++] = 0x0A;
                    RFM_RX_buffer[RFM_numBytesRec++] = 0x0D;
                    RFM_numBytesRec=0;

                    if ( (RFM_RX_buffer[0]=='P') &&
                         (RFM_RX_buffer[1]=='O') &&
                         (RFM_RX_buffer[2]=='N') &&
                         (RFM_RX_buffer[3]=='G') 
                        )
                    {
                        vmon;  
                        __delay_ms(2500);
                        __delay_ms(2500);
                        vmoff;
                        __delay_ms(200);
                    }
                    else
                        __nop();
                }         
                ciclo = 250;
                __nop();
            }
        } //for ciclo
    } //while (1))
}
//////////////////////////////////////////////////////////////////////
// EEPROM
//#include "EEPROM____256.c"

//// eof