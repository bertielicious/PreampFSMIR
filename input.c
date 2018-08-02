/*
 * File:   input.c
 * Author: philip
 *
 * Created on 28 April 2018, 19:55
 */


#include <xc.h>
#include "input.h"
#include "config.h"
#include "write_character.h"



void input(void) 
{
    write_character(&i[0],0x0f,0xb0);  //do this
    write_character(&n[0],0x1f, 0xb0); 
    write_character(&p[0],0x2f, 0xb0);
    write_character(&u[0],0x3f,0xb0);  
    write_character(&t[0],0x4f,0xb0); 
    return;
}
