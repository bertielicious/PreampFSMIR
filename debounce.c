/*
 * File:   debounce.c
 * Author: Phil
 *
 * Created on 05 May 2018, 21:52
 */


#include <xc.h>
#include "config.h"
#include "debounce.h"
#include <stdbool.h>


bool debounce(bool button) 
{
    
    if (button == HI && status == off)
    {
        status = off;
        return 0;
    }
    if (button == LO && status == off)
    {
        status = bouncingOn;
        return 0;
    }
    
    if (button == HI && status == bouncingOn)
    {
        status = off;
        return 0;
    }
    if (button == LO && status == bouncingOn)
    {
        status = on;
        return 1;
    }
    
    if (button == LO && status == on)
    {
        status = on;
        return 1;
    }
    if (button == HI && status == on)
    {
        status = bouncingOff;
        return 0;
    }
    
    if (button == LO && status == bouncingOff)
    {
        status = on;
        return 0;
    }
    if (button == HI && status == bouncingOff)
    {
        status = off;
        return 0;
    }
    
}
