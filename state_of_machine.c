/* FINAL CODE
 * File:   state_of_machine.c
 * Author: philip
 * version 16.4.18.1
 * Created on Monday 16 April 2018, 14:44
 */
#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "clear_oled.h"
#include "write_character.h"
#include "bar_graph.h"
#include "get_digit.h"
#include "split_digits.h"
#include "mute.h"
#include "setup_vol_scrn.h"
#include "input.h"
#include "select_ip.h"
#include "update_PGA2311.h"
#include "vol.h"
#include "state_of_machine.h"

void state_of_machine(int *c_state) // *c_state is initially == VOL state
{ 
    static int temp_vol;
    
  switch (*c_state)
    {           
      case STREAM: 
          if(SWIP == HI)
          {
              c_state = STREAM;
              write_character(&s[0],0x0f,0xb0);  //write stream on oled
              write_character(&t[0],0x1f, 0xb0); 
              write_character(&r[0],0x2f, 0xb0);
              write_character(&e[0],0x3f,0xb0);  
              write_character(&a[0],0x4f,0xb0);
              write_character(&m[0],0x5f,0xb0);  
              vol();
              update_PGA2311(count * 2); 
              temp_vol = count;
              temp_state = *c_state;
             
          }
          else if (SWIP == LO)
          {
             temp_state = *c_state;
              T1CONbits.TMR1ON = 1;
              while(SWIP == LO);    // wait until SWIP is released
              if(time_out >= 1 && time_out <= 11)   // short
              {
               *c_state = MUTE;  
               T1CONbits.TMR1ON = 0;
               time_out = 0; 
              }
              else if(time_out >= 12 && time_out <=30)// long
              {
                  *c_state = PHONO;
                  temp_state = *c_state;
                  T1CONbits.TMR1ON = 0;
                time_out = 0; 
              }
          }
                break;
      case PHONO:
          if(SWIP == HI)
          {
              *c_state = PHONO;
              write_character(&space[0],0x0f,0xb0);  //write stream on oled
              write_character(&p[0],0x1f, 0xb0); 
              write_character(&h[0],0x2f, 0xb0);
              write_character(&o[0],0x3f,0xb0);  
              write_character(&n[0],0x4f,0xb0);
              write_character(&o[0],0x5f,0xb0);    
              vol();
              update_PGA2311(count * 2); 
              temp_vol = count;
              temp_state = *c_state;
          }
              else if (SWIP == LO)
          {
              temp_state = *c_state;
              T1CONbits.TMR1ON = 1;
              while(SWIP == LO);
              if(time_out >= 1 && time_out <= 11)
              {
               *c_state = MUTE;  
               T1CONbits.TMR1ON = 0;
               time_out = 0; 
              }
              else if(time_out >= 12 && time_out <=30)// long
              {
                  *c_state = CD;
                  temp_state = *c_state;
                  T1CONbits.TMR1ON = 0;
                time_out = 0; 
              }
          }
                 break;
      case CD:
          if(SWIP == HI)
          {
              *c_state = CD;
              write_character(&space[0],0x0f,0xb0);  //write stream on oled
              write_character(&space[0],0x1f,0xb0); 
              write_character(&c[0],0x2f, 0xb0);
              write_character(&d[0],0x3f,0xb0);  
              write_character(&space[0],0x4f,0xb0);
              write_character(&space[0],0x5f,0xb0);    
              vol();
              update_PGA2311(count * 2); 
              temp_vol = count;
              
              temp_state = *c_state;
          }
              else if (SWIP == LO)
          {
              
              temp_state = *c_state;
              T1CONbits.TMR1ON = 1;
              while(SWIP == LO);
              if(time_out >= 1 && time_out <= 11)
              {
               *c_state = MUTE;  
               T1CONbits.TMR1ON = 0;
               time_out = 0; 
              }
              else if(time_out >= 12 && time_out <=30)// long
              {
                  *c_state = TUNER;
                  temp_state = *c_state;
                  T1CONbits.TMR1ON = 0;
                time_out = 0; 
              }
          }
                break;
      case TUNER:
          if(SWIP == HI)
          {
              *c_state = TUNER;
              write_character(&space[0],0x0f,0xb0);  //write stream on oled
              write_character(&t[0],0x1f,0xb0); 
              write_character(&u[0],0x2f, 0xb0);
              write_character(&n[0],0x3f,0xb0);  
              write_character(&e[0],0x4f,0xb0);
              write_character(&r[0],0x5f,0xb0);    
              vol();
              update_PGA2311(count * 2); 
              temp_vol = count;
             
              temp_state = *c_state;
          }
              else if (SWIP == LO)
          {
              temp_state = *c_state;
             
              T1CONbits.TMR1ON = 1;
              while(SWIP == LO);
              if(time_out >= 1 && time_out <= 11)
              {
               *c_state = MUTE;  
               T1CONbits.TMR1ON = 0;
               time_out = 0; 
              }
              else if(time_out >= 12 && time_out <=30)// long
              {
                  *c_state = STREAM;
                  temp_state = *c_state;
                  T1CONbits.TMR1ON = 0;
                time_out = 0; 
              }
          }
          break;
          
      case MUTE:
          if(SWIP == HI)
          {
            *c_state = MUTE;
            write_character(&space[0],0x0f,0xb3);
            write_character(&m[0],0x1f,0xb3);  //do this
            write_character(&u[0],0x2f, 0xb3); 
            write_character(&t[0],0x3f, 0xb3);
            write_character(&e[0],0x4f,0xb3);
            count = 0;
            update_PGA2311(count);  
            time_out = 0;
          }
          else if (SWIP == LO)
          {
             T1CONbits.TMR1ON = 1;
             while(SWIP == LO);
             if(time_out >= 1 && time_out <= 11)
              {
               T1CONbits.TMR1ON = 0;
               time_out = 0;
               *c_state = temp_state;
               count = temp_vol;
               vol();
               update_PGA2311(count * 2);   
              }
             else if(time_out >= 12 && time_out <=30)// long
              {
                  *c_state = MUTE;
                  //T1CONbits.TMR1ON = 0;
                  time_out = 0; 
              } 
          }
          break;
          }
    }

  

   