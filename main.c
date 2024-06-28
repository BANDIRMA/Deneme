#include "mcc_generated_files/mcc.h"

// Global Variables
uint8_t VehicleSpeed;
bool SpeedInfoReceived = false;

// Delay Functions
void delay_ms(uint16_t ms) {
    for (uint16_t i = 0; i < ms; i++) {
        __delay_ms(1);
    }
}

void delay_us(uint16_t us) {
    for (uint16_t i = 0; i < us; i++) {
        __delay_us(1);
    }
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    // Initial state of LEDs
    IO_RC1_SetHigh(); // LED on RC1 (Pin 12) on
    IO_RC4_SetLow();  // LED on RC2 (Pin 15) off

    while (1)
    {
        // Blink LED on RC1 at 1 Hz if no speed info received
        if (!SpeedInfoReceived) {
            IO_RC1_Toggle();
            delay_ms(500);
        } else {
            IO_RC1_SetHigh(); // Keep the LED on once speed info is received
        }

        // Check vehicle speed every second
        if (ECAN_ReceiveVehicleSpeed()) {
            // Indicate that vehicle speed was received by blinking LED_RC1 quickly
            for (int i = 0; i < 5; i++) {
                IO_RC1_SetHigh();
                delay_ms(100);
                IO_RC1_SetLow();
                delay_ms(100);
            }
            
            if (VehicleSpeed > 20) {
                // Blink LED on RC2 at 20 Hz
                for (int i = 0; i < 20; i++) {
                    IO_RC4_SetHigh();
                    delay_us(25);
                    IO_RC4_SetLow();
                    delay_us(25);
                }
            } else if (VehicleSpeed < 18) {
                // Blink LED on RC2 at 1 Hz
                IO_RC4_Toggle();
                delay_ms(500);
            }
            
            SpeedInfoReceived = true; // Mark that speed info has been received
        }
    }
}
