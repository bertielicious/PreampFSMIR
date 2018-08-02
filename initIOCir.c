#include <xc.h>
#include "config.h"
void initIOCir(void)
{
  INTCONbits.GIE = 1;           // enable global interrupts
  INTCONbits.IOCIE = 0;         // disables IOC interrupt (master switch))
  UCONbits.USBEN = 0;           // disable USB module  
  INTCONbits.IOCIF = 0;         // clear IOC interrupt flag
  
  IOCBPbits.IOCBP5 = 0;         // disable detection of rising edges on RB5 pin 12
  IOCBNbits.IOCBN5 = 0;         // disable detection of falling edges on RB5 pin 12
  IOCBFbits.IOCBF5 = 0;         // clear IOC FLAG FOR RB5 pin 12 
}
