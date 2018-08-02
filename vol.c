#include "vol.h"
#include "config.h"
#include "bar_graph.h"
#include "split_digits.h"
#include "get_digit.h"
#include "write_character.h"
void vol (void)
{
    if (SWIP == HI)
            {   
                time_out = 0;
                T1CONbits.TMR1ON = 0; 
                if (count >= COUNT_MAX)
                {
                    count = COUNT_MAX;
                }
                if(count <= COUNT_MIN)
                {
                    count = COUNT_MIN;
                }
                temp = count;
                bar_graph();
                split_digits();
                if(count >=0 && count <95)
                {
                    write_character(&minus[0], 0x0f,0xb3);
                }
                else
                {
                    write_character(&space[0],0x0f,0xb3);
                }   
            get_digit(tens, 0x1f);
            get_digit(units, 0x2f); 
            write_character(&d[0],0x3f,0xb3);
            write_character(&B[0],0x4f,0xb3);
    }
}
