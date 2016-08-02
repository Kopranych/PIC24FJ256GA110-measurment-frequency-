
#include "SPI.h"

void spi_init()
{
    _SPI1IF = 0;
    TRIS_SPI = 0;
    mapping_pin_spi();
    SPI1STATbits.SPIEN = 0;
    SPI1CON1 = 0;
    SPI1CON1bits.DISSCK = 0;
    SPI1CON1bits.DISSDO = 0;
    SPI1CON1bits.MODE16 = 1;
    SPI1CON1bits.MSTEN = 1;
    SPI1CON2bits.FRMEN = 1;
    SPI1CON2bits.SPIFSD = 0;
    SPI1CON2bits.SPIFPOL = 0;
    SPI1STATbits.SPIEN = 1;
}
unsigned int spi_txrx(unsigned int data)
{
    unsigned int temp;
    SPI1BUF = data;
    while(_SPI1IF == 0);
    _SPI1IF = 0;
    temp = SPI1BUF;
    return temp;
}

void spi_txrx_AD5312(unsigned int data)
{
 
    spi_txrx(data<<2);
}


void mapping_pin_spi()
{
    __builtin_write_OSCCONL(OSCCON & 0xbf);//Unlock Registers use C30 built-in macro
    RPOR10bits.RP21R = 7;//assign output MOSI
    RPOR13bits.RP26R = 8;//assign output SCK
    RPOR9bits.RP19R = 9;//assign output SS
    __builtin_write_OSCCONL(OSCCON | 0x40);//Lock Registers use C30 built-in macro
}


