#include "LED.h"






void init_port_led()
{
    TRIS_LED &= ~((1<<RD0)|(1<<RD1)|(1<<RD2));
    PORT_LED &= ~((1<<RD0)|(1<<RD1)|(1<<RD2));
    
}


void invers_led1()
{
    PORT_LED ^= 1<<RD0;
}

void invers_led2()
{
    PORT_LED ^= 1<<RD1;
}

void led3_off()
{
    PORT_LED &= ~(1<<RD2);
}

void led3_on()
{
    PORT_LED |= 1<<RD2;
}

void init_port_led_value()
{
    PORT_LED_VALUE = 0;
    TRIS_LED_VALUE = 0;
}

void output_value(unsigned long int value_freq)
{
    PORT_LED_VALUE = value_freq;
}
