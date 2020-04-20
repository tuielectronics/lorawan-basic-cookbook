/*
 * board.h
 *
 *  Created on: Apr 19, 2020
 *      Author: cj
 */

#ifndef __BOARD_H_
#define __BOARD_H_
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "stm32l1xx_hal.h"
#include "utilities.h"
#include "board-timer.h"
#include "board-gpio.h"
#include "board-spi.h"
#include "radio.h"
#include "sx1276.h"
#include "sx1276-board.h"

#define RADIO_DIO_0                                 PB_11
#define RADIO_DIO_1                                 PB_10
#define RADIO_DIO_2                                 PB_1
#define RADIO_DIO_3                                 PB_0

#define RADIO_RESET                                 PA_3

#define RADIO_NSS                                   PA_4
#define RADIO_SCLK                                  PA_5
#define RADIO_MISO                                  PA_6
#define RADIO_MOSI                                  PA_7

void BoardDisableIrq( void );
void BoardEnableIrq( void );

/*!
 * Blocking delay of "s" seconds
 */
void Delay( float s );

/*!
 * Blocking delay of "ms" milliseconds
 */
void DelayMs( uint32_t ms );

uint8_t BoardGetBatteryLevel( void );

void Board_Init(void);
uint32_t Board_Timer_Test(uint32_t timeout);
#endif /* BOARD_H_ */
