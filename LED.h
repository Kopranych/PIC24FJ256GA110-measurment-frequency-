/* 
 * File:   LED.h
 * Author: Kopranov_IN
 *
 * Created on 20 ???? 2016 ?., 16:14
 */

#include <p24fj256ga110.h>



#define PORT_LED PORTD
#define TRIS_LED TRISD
#define PORT_LED_VALUE PORTB
#define TRIS_LED_VALUE TRISB
#define RD0 0
#define RD1 1
#define RD2 2

void init_port_led();
void invers_led1();
void invers_led2();
void led3_off();
void led3_on();
void init_port_led_value();
void output_value(unsigned long int value_freq);
