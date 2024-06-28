/**
  @Generated PIC10 / PIC12 / PIC16 / PIC18 MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K80
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above or later
        MPLAB             :  MPLAB X 6.00
*/



#include "mcc.h"


void SYSTEM_Initialize(void)
{

    INTERRUPT_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    TMR0_Initialize();
    ECAN_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // SCS FOSC; HFIOFS not stable; IDLEN disabled; IRCF 8MHz_HF; 
    OSCCON = 0x60;
    // SOSCGO disabled; MFIOSEL disabled; SOSCDRV Low Power; 
    OSCCON2 = 0x00;
    // INTSRC INTRC; PLLEN disabled; TUN 0; 
    OSCTUNE = 0x00;
    // ROSEL System Clock(FOSC); ROON disabled; ROSSLP Disabled in Sleep mode; RODIV Fosc; 
    REFOCON = 0x00;
}


/**
 End of File
*/
