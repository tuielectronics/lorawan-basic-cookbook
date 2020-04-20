/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board SPI driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#ifndef __BOARD_SPI_H__
#define __BOARD_SPI_H__

/*!
 * SPI driver structure definition
 */
//#include "stm32l1xx.h"
//#include "board.h"
//#include "spi-board.h"
//#include "stm32l1xx_hal_spi.h"
struct Spi_s
{
    SPI_HandleTypeDef Spi;
    Gpio_t Mosi;
    Gpio_t Miso;
    Gpio_t Sclk;
    Gpio_t Nss;
};
/*!
 * SPI object type definition
 */
typedef struct Spi_s Spi_t;

void SpiInit( Spi_t *obj, PinNames mosi, PinNames miso, PinNames sclk, PinNames nss );
uint16_t SpiInOut( Spi_t *obj, uint16_t outData );
#endif  // __BOARD_SPI_MCU_H__
