/* 
 * File:   main.c
 * Author: Kopranov_IN
 * Пограмма для подсчета частоты входных сигналов за 
 * эталонный промежуток времени
 * Created on 15 ???? 2016 ?., 9:43
 * руссике коменты на 1251
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24fj256ga110.h>
#include <p24Fxxxx.h>
#include "InterruptVector.h"
#include "Timer.h"
#include "LED.h"
#include "calculation.h"
//#include "InputCapture.h"

#define NUMMEAS 6//number measurments
#define VALUE_CAUNTER_L TMR2
#define VALUE_CAUNTER_H TMR3





int CONFIG3 __attribute__((space(prog), address(0x2ABFA))) = 0xFFFF ;
//_CONFIG3(
//    WPFP_WPFP511 &       // Write Protection Flash Page Segment Boundary (Highest Page (same as page 170))
//    WPDIS_WPDIS &        // Segment Write Protection Disable bit (Segmented code protection disabled)
//    WPCFG_WPCFGDIS &     // Configuration Word Code Page Protection Select bit (Last page(at the top of program memory) and Flash configuration words are not protected)
//    WPEND_WPENDMEM       // Segment Write Protection End Page Select bit (Write Protect from WPFP to the last page of memory)
//);
 int CONFIG2 __attribute__((space(prog), address(0x2ABFC))) = 0x77DF ;
//_CONFIG2(
//    POSCMOD_NONE &       // Primary Oscillator Select (Primary oscillator disabled)
//    I2C2SEL_PRI &        // I2C2 Pin Select bit (Use Default SCL2/SDA2 pins for I2C2)
//    IOL1WAY_ON &         // IOLOCK One-Way Set Enable bit (Write RP Registers Once)
//    OSCIOFNC_ON &        // Primary Oscillator Output Function (OSCO functions as port I/O (RC15))
//    FCKSM_CSDCMD &       // Clock Switching and Monitor (Both Clock Switching and Fail-safe Clock Monitor are disabled)
//    FNOSC_FRCDIV &       // Oscillator Select (Fast RC oscillator with Postscaler (FRCDIV))
//    IESO_OFF             // Internal External Switch Over Mode (IESO mode (Two-speed start-up)disabled)
//);
 int CONFIG1 __attribute__((space(prog), address(0x2ABFE))) = 0x6F60 ;
//_CONFIG1(
//    WDTPS_PS1 &          // Watchdog Timer Postscaler (1:1)
//    FWPSA_PR32 &         // WDT Prescaler (Prescaler ratio of 1:32)
//    WINDIS_OFF &         // Watchdog Timer Window (Standard Watchdog Timer is enabled,(Windowed-mode is disabled))
//    FWDTEN_OFF &         // Watchdog Timer Enable (Watchdog Timer is disabled)
//    ICS_PGx1 &           // Comm Channel Select (Emulator functions are shared with PGEC1/PGED1)
//    GWRP_ON &            // General Code Segment Write Protect (Writes to program memory are disabled)
//    GCP_OFF &            // General Code Segment Code Protect (Code protection is disabled)
//    JTAGEN_ON            // JTAG Port Enable (JTAG port is enabled)
//);




enum current_account{ //крутим карусель 
    mode1,
    mode2,
    mode3,
    mode4,
    mode5,
    mode6
}mode;

float current_value = 0, medium_value = 0;
unsigned int DAC_current = IDEAL_VALUE;


int main(void)
{   
//    _CONFIG2( OPT1_ON & OPT2_OFF & OPT3_PLL );
//    #define SYSCLK 32000000
//    int CONFIG1 __attribute__((space(prog), address(0x2ABFE))) = 0x7FFF ;
    AD1PCFGL = 0xffff;//порт в режим ввода/вывода цифровых сигналов
	init_timer1();
    init_timer23();//
    start_timer1_23();
    init_port_led();
    init_port_led_value();
	while(1)
	{	
        while(flag_interrupt)//как только сработало прерывание включается флаг прерывания
        {
            _T1IE = 0;//disable interrupt
            if(mode == mode6)
            {    
                current_value = (value_freqH<<16)|(value_freqL);
                medium_value += current_value;//сохраняем сумму значений частоты за N измерений       
//              medium_value = medium_value/NUMMEAS;
//              SPI = medium_value;
                mode = mode1;//переключаем карусель в начало
                invers_led2();
                output_value(current_value);
//                FLAG1 = 1;
                flag_interrupt = 0;//сбрасываем флаг 
                medium_value = 0;//сбрасываем среднее значение которое уже отправили на ЦАП 
                current_value = 0;
            }
            else
            {      
                current_value = (value_freqH<<16)|(value_freqL);
                medium_value += current_value;//сохраняем сумму значений 
                calcul_freq(current_value, DAC_current);
//              SPI = current_value - ideal_value;
                
                output_value(current_value);
//                timer3 = 0;
                invers_led1();
                current_value = 0;
                mode++;//переходим к следующему замеру частоты
//                FLAG2 = 1;
                flag_interrupt = 0;//сбрасываем флаг                 
            }
            _T1IE = 1;//enable interrupt
        }
        if(current_value > 0)
        {
            led3_off();
        }
        else led3_on();       
   	}   
	return 1;
}

