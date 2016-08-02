/* 
 * File:   SPI.h
 * Author: Kopranov_IN
 *
 * Created on 29 Èþëü 2016 ã., 13:22
 */

#include <p24fj256ga110.h>

#define SPI_MOSI TRISG6 = 0
#define SPI_SCK TRISG7 = 0
#define SPI_SS TRISG8 = 0
#define TRIS_SPI TRISG
#define PORT_SPI PORTG

void spi_init();
unsigned int spi_txrx(unsigned int data);
void spi_txrx_AD5312(unsigned int data);
void mapping_pin_spi();
