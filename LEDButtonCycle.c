/******************************************************
Chip type : ARM TM4C123GH6PM
Program type : Firmware
Core Clock frequency: 80.000000 MHz
*******************************************************/

#include <stdbool.h>                //Importing Libraries
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_i2c.h"
#include "driverlib/i2c.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

void button();                    //declaring a function called button

void main(void) {
    
    // Setting the internal clock
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);                                    // Enable Peripheral ports for input/ output
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);      //PORTC enabled        
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7);  // LED 1 LED 2

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);                 //PORTB
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);         // LED 4

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);              //PORT D
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);         // LED 3
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_2);         // BTN 1

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);                  //PORT F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); 
// RGB LED on Launchpad
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);                  //PORT A
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_6);         // Switch 2

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);                  //PORT E
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_0);         // BTN 2

    while(1)
    {
          button();                        //checking to see if button was called
if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6)){        // Listen for the switch
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
 // LED Blue on Launchpad
/* Cycle through the LEDs on the Orbit board    //LED pins(1-4) 
PC6 = 0X40= LED 1                                              
PC7 = 0X80 = LED 2                                            PD6 = 0X40 = LED 3                                        
PB5 = 0X20 = LED 4
*/

            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20); // LED 4 on
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00); // LED 3 off
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x00); // LED 1 & 2 off

            SysCtlDelay(2000000);             // Delay, Replaces for LOOP

            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x40); // LED 3 on
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0X00); //Turns LED 4 off

            SysCtlDelay(2000000);             // Delay, Replaces for LOOP

            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x00); //LED 1 off
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0x80); // LED 2 on
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00); // LED 3 off

            SysCtlDelay(2000000);             // Delay, Replaces for LOOP

            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0x00); // LED 2 off
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x40); // LED 1 on

            SysCtlDelay(2000000);             // Delay, Replaces for LOOP
        }
        else{
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8); 
//  LED Green on Launchpad
            // Cycle through the LEDs on the Orbit board
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x00); // LED 1 & 2 Off
GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00); // LED 3 off            
GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20); // LED 4 on

            SysCtlDelay(2000000);         // Delay, Replaces for LOOP

            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00); // LED 4 off
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x40); // LED 3 on

            SysCtlDelay(2000000);         // Delay, Replaces for LOOP

            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x80); // LED 1 & 2 on
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00); // LED 3 off

            SysCtlDelay(2000000);         // Delay, Replaces for LOOP

            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x40); // LED 1 & 2 Off

            SysCtlDelay(2000000);         // Delay, Replaces for LOOP
        }

        while(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2)){     // Listen for BTN 1

            // All LED Blink - PORTs C,D, and B are for the orbit LEDs and F is for the LaunchPad
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0xFF);
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0xFF);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0xFF);
 // White Output with all on in PORT F
            SysCtlDelay(2000000);            //Delay

            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x00);
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00); 
                                //All LEDs turn off 
            SysCtlDelay(2000000);            //Delay
        }
    }     //while loop close for logical 1
}    //int main close

void button(){                                //returns void
    while(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_0)){            //while BTN 2 is pressed
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x02);  // Red led turns on

/*continues the cycles of the 4 LEDs on the orbit since calling this function breaks out of their while loop*/
      
      GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20);             // LED 4 on
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00);             // LED 3 of
                    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x00);     // LED 1 & 2 off

                    SysCtlDelay(2000000);         // Delay, Replaces for LOOP

                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x40);             // LED 3 on
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0X00);         //Turns LED 4 off

                    SysCtlDelay(2000000);         // Delay, Replaces for LOOP

                    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x00);             //LED 1 off
                    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0x80);             // LED 2 on
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00);             // LED 3 off

                    SysCtlDelay(2000000);         // Delay, Replaces for LOOP

                    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0x00);             // LED 2 off
                    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x40);             // LED 1 on

                    SysCtlDelay(2000000);         // Delay, Replaces for LOOP
                }
    }
