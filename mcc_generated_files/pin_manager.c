/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K80
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB             :  MPLAB X 6.00

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/



#include "pin_manager.h"





void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x02;

    /**
    TRISx registers
    */
    TRISA = 0xEF;
    TRISB = 0xFB;
    TRISC = 0xED;

    /**
    ANSELx registers
    */
    ANCON0 = 0x1F;
    ANCON1 = 0x07;

    /**
    WPUx registers
    */
    WPUB = 0x00;
    INTCON2bits.nRBPU = 1;






   
    // Enable RBI interrupt 
    INTCONbits.RBIE = 1; 
    
}
  
void PIN_MANAGER_IOC(void)
{   
	// Clear global Interrupt-On-Change flag
    INTCONbits.RBIF = 0;
}

/**
 End of File
*/