/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define VD_TRIS                 TRISAbits.TRISA0
#define VD_LAT                  LATAbits.LATA0
#define VD_PORT                 PORTAbits.RA0
#define VD_WPU                  WPUAbits.
#define VD_OD                   ODCONAbits.
#define VD_ANS                  ANSELAbits.ANSA0
#define VD_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define VD_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define VD_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define VD_GetValue()           PORTAbits.RA0
#define VD_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define VD_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define VD_SetPullup()          do { WPUAbits. = 1; } while(0)
#define VD_ResetPullup()        do { WPUAbits. = 0; } while(0)
#define VD_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define VD_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define VD_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define VD_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
// get/set IO_RA1 aliases
#define VM_TRIS                 TRISAbits.TRISA1
#define VM_LAT                  LATAbits.LATA1
#define VM_PORT                 PORTAbits.RA1
#define VM_WPU                  WPUAbits.
#define VM_OD                   ODCONAbits.
#define VM_ANS                  ANSELAbits.ANSA1
#define VM_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define VM_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define VM_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define VM_GetValue()           PORTAbits.RA1
#define VM_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define VM_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define VM_SetPullup()          do { WPUAbits. = 1; } while(0)
#define VM_ResetPullup()        do { WPUAbits. = 0; } while(0)
#define VM_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define VM_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define VM_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define VM_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RA2 aliases
#define DIO1_TRIS                 TRISAbits.TRISA2
#define DIO1_LAT                  LATAbits.LATA2
#define DIO1_PORT                 PORTAbits.RA2
#define DIO1_WPU                  WPUAbits.
#define DIO1_OD                   ODCONAbits.
#define DIO1_ANS                  ANSELAbits.ANSA2
#define DIO1_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define DIO1_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define DIO1_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define DIO1_GetValue()           PORTAbits.RA2
#define DIO1_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define DIO1_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define DIO1_SetPullup()          do { WPUAbits. = 1; } while(0)
#define DIO1_ResetPullup()        do { WPUAbits. = 0; } while(0)
#define DIO1_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define DIO1_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define DIO1_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define DIO1_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA3 aliases
#define CSN_TRIS                 TRISAbits.TRISA3
#define CSN_LAT                  LATAbits.LATA3
#define CSN_PORT                 PORTAbits.RA3
#define CSN_WPU                  WPUAbits.
#define CSN_OD                   ODCONAbits.
#define CSN_ANS                  ANSELAbits.ANSA3
#define CSN_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define CSN_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define CSN_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define CSN_GetValue()           PORTAbits.RA3
#define CSN_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define CSN_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define CSN_SetPullup()          do { WPUAbits. = 1; } while(0)
#define CSN_ResetPullup()        do { WPUAbits. = 0; } while(0)
#define CSN_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define CSN_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define CSN_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define CSN_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)
// get/set IO_RA4 aliases
#define SCK_TRIS                 TRISAbits.TRISA4
#define SCK_LAT                  LATAbits.LATA4
#define SCK_PORT                 PORTAbits.RA4
#define SCK_WPU                  WPUAbits.
#define SCK_OD                   ODCONAbits.
#define SCK_ANS                  ANSELAbits.ANSA4
#define SCK_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SCK_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SCK_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SCK_GetValue()           PORTAbits.RA4
#define SCK_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SCK_SetPullup()          do { WPUAbits. = 1; } while(0)
#define SCK_ResetPullup()        do { WPUAbits. = 0; } while(0)
#define SCK_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define SCK_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define SCK_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define SCK_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RB0 aliases
#define DIO0_TRIS                 TRISBbits.TRISB0
#define DIO0_LAT                  LATBbits.LATB0
#define DIO0_PORT                 PORTBbits.RB0
#define DIO0_WPU                  WPUBbits.WPUB0
#define DIO0_OD                   ODCONBbits.
#define DIO0_ANS                  ANSELBbits.
#define DIO0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define DIO0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define DIO0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define DIO0_GetValue()           PORTBbits.RB0
#define DIO0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define DIO0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define DIO0_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define DIO0_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define DIO0_SetPushPull()        do { ODCONBbits. = 0; } while(0)
#define DIO0_SetOpenDrain()       do { ODCONBbits. = 1; } while(0)
#define DIO0_SetAnalogMode()      do { ANSELBbits. = 1; } while(0)
#define DIO0_SetDigitalMode()     do { ANSELBbits. = 0; } while(0)
// get/set IO_RB1 aliases
#define MOSI_TRIS                 TRISBbits.TRISB1
#define MOSI_LAT                  LATBbits.LATB1
#define MOSI_PORT                 PORTBbits.RB1
#define MOSI_WPU                  WPUBbits.WPUB1
#define MOSI_OD                   ODCONBbits.
#define MOSI_ANS                  ANSELBbits.ANSB1
#define MOSI_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define MOSI_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define MOSI_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define MOSI_GetValue()           PORTBbits.RB1
#define MOSI_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define MOSI_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define MOSI_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define MOSI_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define MOSI_SetPushPull()        do { ODCONBbits. = 0; } while(0)
#define MOSI_SetOpenDrain()       do { ODCONBbits. = 1; } while(0)
#define MOSI_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define MOSI_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)
// get/set IO_RB3 aliases
#define MISO_TRIS                 TRISBbits.TRISB3
#define MISO_LAT                  LATBbits.LATB3
#define MISO_PORT                 PORTBbits.RB3
#define MISO_WPU                  WPUBbits.WPUB3
#define MISO_OD                   ODCONBbits.
#define MISO_ANS                  ANSELBbits.ANSB3
#define MISO_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define MISO_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define MISO_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define MISO_GetValue()           PORTBbits.RB3
#define MISO_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define MISO_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define MISO_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define MISO_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define MISO_SetPushPull()        do { ODCONBbits. = 0; } while(0)
#define MISO_SetOpenDrain()       do { ODCONBbits. = 1; } while(0)
#define MISO_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define MISO_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)
// get/set IO_RB4 aliases
#define RSTRFM_TRIS                 TRISBbits.TRISB4
#define RSTRFM_LAT                  LATBbits.LATB4
#define RSTRFM_PORT                 PORTBbits.RB4
#define RSTRFM_WPU                  WPUBbits.WPUB4
#define RSTRFM_OD                   ODCONBbits.
#define RSTRFM_ANS                  ANSELBbits.ANSB4
#define RSTRFM_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RSTRFM_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RSTRFM_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RSTRFM_GetValue()           PORTBbits.RB4
#define RSTRFM_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RSTRFM_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RSTRFM_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define RSTRFM_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define RSTRFM_SetPushPull()        do { ODCONBbits. = 0; } while(0)
#define RSTRFM_SetOpenDrain()       do { ODCONBbits. = 1; } while(0)
#define RSTRFM_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define RSTRFM_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

#endif // PINS_H
/**
 End of File
*/