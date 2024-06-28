/*******************************************************************************
  TMR0 Generated Driver File

  Company:
    Microchip Technology Inc.

  File Name:
    tmr0.c

  Summary:
    This is the generated driver implementation file for the TMR0 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This source file provides APIs for TMR0.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K80
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB             :  MPLAB X 6.00
*******************************************************************************/

#include <xc.h>
#include "tmr0.h"
#include "pin_manager.h"
// Örne?in, tmr0.c içinde global olarak tan?mlayabilirsiniz:
extern uint8_t VehicleSpeed; // main.c veya uygun ba?ka bir dosyada tan?ml? oldu?unu varsayarak

extern bool SpeedInfoReceived; // main.c veya uygun ba?ka bir dosyada tan?ml? oldu?unu varsayarak

/**
  Section: Global Variables Definitions
*/

void (*TMR0_InterruptHandler)(void);

volatile uint16_t timer0ReloadVal;

/**
  Section: TMR0 APIs
*/


void TMR0_Initialize(void)
{
    // Set TMR0 to the options selected in the User Interface

    //Enable 16bit timer mode before assigning value to TMR0H
    T0CONbits.T08BIT = 0;

    // TMR0H 240;
    TMR0H = 0xF0;

    // TMR0L 189;
    TMR0L = 0xBD;

    // Load TMR0 value to the 16-bit reload variable
    timer0ReloadVal = (uint16_t)((TMR0H << 8) | TMR0L);

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;

    // Set Default Interrupt Handler
    TMR0_SetInterruptHandler(TMR0_DefaultInterruptHandler);

    // T0PS 1:256; T08BIT 16-bit; T0SE Increment_hi_lo; T0CS FOSC/4; TMR0ON enabled; PSA assigned;
    T0CON = 0x97;
}

void TMR0_StartTimer(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 1;
}

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 0;
}

uint16_t TMR0_ReadTimer(void)
{
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow  = TMR0L;
    readValHigh = TMR0H;
    readVal  = ((uint16_t)readValHigh << 8) + readValLow;

    return readVal;
}

void TMR0_WriteTimer(uint16_t timerVal)
{
    // Write to the Timer0 register
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}

void TMR0_Reload(void)
{
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal >> 8;
    TMR0L = (uint8_t) timer0ReloadVal;
}

void TMR0_ISR(void)
{
    // Clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    // Reload TMR0
    TMR0_Reload();

    // Call the user-defined interrupt handler, if defined
    if (TMR0_InterruptHandler)
    {
        TMR0_InterruptHandler();
    }
    if (SpeedInfoReceived) {
        if (VehicleSpeed > 20) {
            LATCbits.LATC1 = 1; // H?z? büyükse LED'i aç
        } else {
            LATCbits.LATC1 = 0; // H?z? küçükse LED'i kapat
        }
    }
}

void TMR0_SetInterruptHandler(void (* InterruptHandler)(void))
{
    TMR0_InterruptHandler = InterruptHandler;
}

void TMR0_DefaultInterruptHandler(void)
{
    // Default interrupt handler for TMR0
    // Implement your TMR0 interrupt code here
    // This example blinks RC1 and RC4 LEDs based on speed conditions

    static uint8_t blinkCount = 0;

    // Toggle RC1 LED (blink at 20 Hz if speed > 20 km/h)
    if (VehicleSpeed > 20)
    {
        if (blinkCount < 10)
        {
            LATCbits.LATC1 = ~LATCbits.LATC1;
        }
        else
        {
            LATCbits.LATC1 = 0; // Ensure RC1 is off
        }
        blinkCount++;
        if (blinkCount >= 20)
        {
            blinkCount = 0;
        }
    }
    else
    {
        LATCbits.LATC1 = 0; // Ensure RC1 is off
    }

    // Toggle RC4 LED (blink at 1 Hz until speed info is received, then stay on)
    if (!SpeedInfoReceived)
    {
        LATCbits.LATC4 = ~LATCbits.LATC4;
    }
    else
    {
        LATCbits.LATC4 = 1; // Ensure RC4 is on
    }
}

/**
  End of File
*/
