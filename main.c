/* 
 * File:   main.c
 * Author: Kopranov_IN
 *
 * Created on 15 ???? 2016 ?., 9:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24fj256ga110.h>
#include "InterruptVector.h"
//#include "InputCapture.h"
#include "Timer.h"
#include "LED.h"

int main(void)
{   
//    _CONFIG2( OPT1_ON & OPT2_OFF & OPT3_PLL );
//    #define SYSCLK 32000000
//    int CONFIG1 __attribute__((space(prog), address(0x2ABFE))) = 0x7FFF ;
    AD1PCFG = 0xffff;//
	init_timer1();
    init_timer23();
    start_timer1_23();
    init_port_led();
	while(1)
	{	
        while(flag_interrupt)
        {
            if(mode == mode6)
            {
                medium_value += current_value;       
//              medium_value = medium_value/NUMMEAS;
//              SPI = medium_value;
                mode = mode1;
                FLAG1 = 1;
                flag_interrupt = 0;
            }
            else
            {
        
                medium_value += current_value;
//              SPI = current_value - ideal_value;
                mode++;
                FLAG2 = 1;
                flag_interrupt = 0;
            }
        }
        if(current_value > 0)
        {
            led3_off();
        }
        else led3_on();
        
        
        
        if(FLAG2)
        {
        
                _T1IE = 0;//disable interrupt
//              SPI = current_value - ideal_value;
                invers_led1();
                FLAG2 = 0;
                _T1IE = 1;//enable interrupt
        }
        if(FLAG1)
        {
                _T1IE = 0;//disable interrupt
 //             medium_value = (medium_value/NUMMEAS) - ideal_value;
//              SPI = medium_value;
                invers_led2();
                medium_value = 0;
                FLAG1 = 0;
                _T1IE = 1;//enable interrupt
        }
	}
    
	return 1;
}

