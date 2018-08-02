/*
 * File:   resetRc5.c
 * Author: Phil
 *
 * Created on 17 July 2018, 15:25
 */


#include <xc.h>
#include"config.h"
#include "main.h"
void resetRc5(void) 
{
    INTCONbits.IOCIE = 0;         // disables IOC interrupt (master switch))
    UCONbits.USBEN = 0;           // disable USB module  
    INTCONbits.IOCIF = 0;         // clear IOC interrupt flag
  
    IOCBPbits.IOCBP5 = 0;         // disable detection of rising edges on RB5 pin 12
    IOCBNbits.IOCBN5 = 0;         // disable detection of falling edges on RB5 pin 12
    IOCBFbits.IOCBF5 = 0;         // clear IOC FLAG FOR RB5 pin 12
    
    has_run = 0;
    pulse_type = SP;
    stateRC5 = MID1;
    RC5_code = 0x0000;
    bits = 14;
    magic_num = 1;
    countRC5 = 0;
}
