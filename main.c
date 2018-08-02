/*
 * File:   main.c
 * Author: Phil
 *
 * Created on 04 May 2018, 21:28
 */


#include <xc.h>
#include "config.h"
#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "init_ports.h"
#include "config_osc.h"
#include "write_command.h"
#include "config_oled.h"
#include "set_page.h"
#include "set_columns.h"
#include "write_data.h"
#include "clear_oled.h"
#include "putch.h"
#include "set_usart.h"
#include "initIOCir.h"
#include "ioc_enable.h"
#include "init_TMR1.h"
#include "init_TMR0.h"
#include "get_digit.h"
#include "write_character.h"
#include "splash_screen.h"
#include "setup_vol_scrn.h"
#include "bar_graph.h"
#include "split_digits.h"
#include "update_PGA2311.h"
#include "resetRc5.h"
#include "state_of_machine.h"
#include "fsm.h"
#include "vol.h"
#include "stateMachine.h"
void main(void) 
{
    count = 0;          // clear count so volume is at minimum at reset/ power on
    init_ports();       // set port directions and SPI setup
    config_osc();       // set osccon bits to generate a 4MHz internal clock
    set_usart();        // setup USART for serial comms with the PC terminal
    init_TMR0();
    init_TMR1();
    config_oled();      // oled now talking to PIC, but with garbage pixels illuminated on oled
    clear_oled();
    splash_screen();
    __delay_ms(5000);
    clear_oled();
    setup_vol_scrn();
    initIOCir();
    stateRC5 = MID1;
    state_of_machine(&current_state);   // FSM for Preamp functions of VOL, MUTE, INPUT, IP_SELECT 
    printf ("\n");
    printf (" PreampFSM\n");
    count = 1;          // initial volume set to -94dB
    
    while(1)
    {   
    start:if(enable_run == 1 )
        {
            state_of_machine(&current_state);   // FSM for Preamp functions of VOL, MUTE, INPUT, IP_SELECT 
            TMR1H = 0x00;
            TMR1L = 0x00;
        }

            //while(IR == HI && has_run !=1);    // wait for first button press on RC5 handset
           // while(IR == LO && has_run !=1);
           // if(IR == HI && has_run !=1)
   if(IR == LO && has_run !=1)
            {
                enable_run = 0;
                bits--;
                INTCONbits.IOCIE = 0;       // master switch disable for interrupt on change   
                has_run = 1;                // this block only runs once until system is reset
                RC5_code = RC5_code | 1<<bits; // generates initial RC5 code S1 of 0x2000
                bits--;
                RC5_code = RC5_code | 1<<bits; // generates initial RC5 code S2 of 0x1000
                bits--;                        // keep track of how many of the 14 RC5 bits have been consumed
                stateRC5 = MID1;
                TMR1H = 0x00;
                TMR1L = 0x00;
                INTCONbits.IOCIE = 1;       // master switch enable for interrupt on change     
                IOCBPbits.IOCBP5 = 0;       // disable interrupt on rising edge
                IOCBNbits.IOCBN5 = 1;       // enable interrupt on falling edge
           
                
        
            }
            else if(IOCIF !=1 && (bits + 1) == 0)  // if no interrupt and all 14 RC5 bits have been consumed by state machine
            //else if(IOCIF !=1 && (bits) == 0)
            {
                printf("RC5 code = %x\n %d", RC5_code, bits);
                resetRc5();
                T1CONbits.TMR1ON = 0;
                enable_run = 1;
                goto start;
            } 
            
                
            
    }
    
 }      
  

