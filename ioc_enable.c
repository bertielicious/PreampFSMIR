/*
 * File:   ioc_enable.c
 * Author: philip
 *
 * Created on 16 April 2018, 19:43
 */


#include <xc.h>

void ioc_enable(void) 
{
    INTCONbits.GIE = 1;         // enable global interrupts
    UCONbits.USBEN = 0;         // disable USB module     
    INTCONbits.IOCIE = 0;       // set interrupt on change to be enabled
   // IOCANbits.IOCAN1 = 1;       // enable negative falling edge trigger on external interrupt on PORTAbits.RA1 pin 18
  //  IOCAFbits.IOCAF1 = 0;       // interrupt flag for RA1 interrupt on change
    /******IR detect *********/
    IOCBPbits.IOCBP5 = 0;         // disable detection of rising edges on RB5 pin 12
    IOCBNbits.IOCBN5 = 0;         // disable detection of falling edges on RB5 pin 12
    IOCBFbits.IOCBF5 = 0;         // clear IOC FLAG FOR RB5 pin 12
    INTCONbits.IOCIF = 0;       // clear IOC interrupt flag to allow any future interrupts
    
}
