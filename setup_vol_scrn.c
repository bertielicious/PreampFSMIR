/*
 * File:   setup_vol_scrn.c
 * Author: philip
 *
 * Created on 18 February 2018, 18:45
 */


#include <xc.h>
#include "config.h"
#include "setup_vol_scrn.h"
#include "write_character.h"
#include "set_page.h"
#include "set_columns.h"
#include "write_data.h"


void setup_vol_scrn(void) 
{
    unsigned char col;
   /* write_character(&s[0],0x0f,0xb0);  //do this
    write_character(&t[0],0x1f, 0xb0); 
    write_character(&r[0],0x2f, 0xb0);
    write_character(&e[0],0x3f,0xb0);  
    write_character(&a[0],0x4f,0xb0);
    write_character(&m[0],0x5f,0xb0);*/
    
    //write_character(&cuatro[0],0x2f,0xb3);    // dummy volume data for testing
   // write_character(&cinco[0],0x3a,0xb3);
    
   
        set_page(0x20,0x00,0xb6);   // draw top line of box enclosing bar graph
        set_columns(0x21, 0x08,0x78);       // columns 8 to 120
        for(col=9;col<120;col++)   
        {
            write_data(0x01);       //msb = 1, rest are 0's
        }
        set_page(0x20,0x00,0xb6);   // 
        set_columns(0x21, 0x08,0x09);
        write_data(0xff);           // draw vertical end to box LHS
    
        set_page(0x20,0x00,0xb7);   // draw bottom line of box enclosing bar graph
        set_columns(0x21, 0x09,0x78);
        for(col=9;col<120;col++)   
        {
            write_data(0x80);       // draw bottom line of page b7 to create a container for bar graph
        }
        set_page(0x20,0x00,0xb7);
        set_columns(0x21, 0x08,0x09);
        write_data(0xff);           // draw vertical end
    
        set_page(0x20,0x00,0xb6);   // 
        set_columns(0x21, 0x77,0x78);
        write_data(0xff);           // draw vertical end to box RHS
        set_page(0x20,0x00,0xb7);
        set_columns(0x21, 0x77,0x78);
        write_data(0xff);           // draw vertical end
        return;
}
