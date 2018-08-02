/*
 * File:   select_ip.c
 * Author: philip
 *
 * Created on 28 April 2018, 20:13
 */


#include <xc.h>
#include "config.h"
#include "write_character.h"
#include "select_ip.h"


void select_ip(void) 
{
    write_character(&s[0],0x0f,0xb0);  //do this
    write_character(&e[0],0x1f, 0xb0); 
    write_character(&l[0],0x2f, 0xb0);
    write_character(&e[0],0x3f,0xb0);  
    write_character(&c[0],0x4f,0xb0); 
    write_character(&t[0],0x5f,0xb0);
    //write_character(&e[0],0x6f,0xb0);
    //write_character(&d[0],0x7f,0xb0);
    return;
}

