/**
  Generated Interrupt Manager Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K80
        Driver Version    :  2.12
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above or later
        MPLAB 	          :  MPLAB X 6.00
*/


#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable high priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptHighEnable();
 */
#define INTERRUPT_GlobalInterruptHighEnable() (INTCONbits.GIEH = 1)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable high priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptHighDisable();
 */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable low priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptLowEnable();
 */
#define INTERRUPT_GlobalInterruptLowEnable() (INTCONbits.GIEL = 1)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable low priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptLowDisable();
 */
#define INTERRUPT_GlobalInterruptLowDisable() (INTCONbits.GIEL = 0)
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable peripheral interrupts.
 * @Example
    INTERRUPT_PeripheralInterruptEnable();
 */
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable peripheral interrupts.
 * @Example
    INTERRUPT_PeripheralInterruptDisable();
 */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes PIC18 peripheral interrupt priorities; enables/disables priority vectors
 * @Example
    INTERRUPT_Initialize();
 */
void INTERRUPT_Initialize (void);

#endif  // INTERRUPT_MANAGER_H
/**
 End of File
*/
