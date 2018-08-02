/*
 * File:   stateMachine.c
 * Author: Phil
 *
 * Created on 07 June 2018, 21:44
 */


#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "stateMachine.h"

void stateMachine(void) 
{
    
    switch (stateRC5)
    {
        case MID1:
                
            if (pulse_type == SP)
            {
                stateRC5 = START1; 
            }
            else if(pulse_type == LP)
            {
                stateRC5 = MID0;
                RC5_code = RC5_code | 0<<bits;
                bits--;
            }
            break;
            
        case START1:
            if(pulse_type == SS)
            {
                stateRC5 = MID1;
                RC5_code = RC5_code | 1<<bits;
                bits--;
            }
            break;
            
        case MID0:
            if(pulse_type == SS)
            {
                stateRC5 = START0; 
            }
            else if(pulse_type == LS)
            {
                stateRC5 = MID1;
                RC5_code = RC5_code | 1<<bits;
                bits--;  
            }
            break;
            
            case START0:
                if(pulse_type == SP)
                {
                    stateRC5 = MID0;
                    RC5_code = RC5_code | 0<<bits;
                    bits--;
                }
                break;
        }      
    }         

