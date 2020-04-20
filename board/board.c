/*
 * board.c
 *
 *  Created on: Apr 19, 2020
 *      Author: cj
 */

#include "board.h"
/*!
* Nested interrupt counter.
*
* \remark Interrupt should only be fully disabled once the value is 0
*/
static uint8_t IrqNestLevel = 0;

void BoardDisableIrq( void )
{
  __disable_irq( );
  IrqNestLevel++;
}

void BoardEnableIrq( void )
{
  IrqNestLevel--;
  if( IrqNestLevel == 0 )
  {
    __enable_irq( );
  }
}
void Delay( float s )
{
    DelayMs( s * 1000.0f );
}

void DelayMs( uint32_t ms )
{
    HAL_Delay( ms );
}
uint8_t BoardGetBatteryLevel( void ){
	return 1;
}
void Board_Init(){
	SpiInit( &SX1276.Spi, RADIO_MOSI, RADIO_MISO, RADIO_SCLK, NC );
	SX1276IoInit( );
	/*
	 * set RTC alarm interrupt here
	 */
	HAL_NVIC_SetPriority( RTC_Alarm_IRQn, 4, 0 );
	HAL_NVIC_EnableIRQ( RTC_Alarm_IRQn );
	DelayMs(500);
}
static TimerEvent_t TestTimer;
volatile static bool TestTimerPassed = false;
static void TestTimerEvent()
{
  TimerStop( &TestTimer );
  TestTimerPassed = true;
}
uint32_t Board_Timer_Test(uint32_t timeout){

	TimerInit( &TestTimer, TestTimerEvent );
	TimerSetValue( &TestTimer, timeout );
	uint32_t timeStart = HAL_GetTick();
	TimerStart( &TestTimer );
	while( TestTimerPassed == false )
	{
	}
	return HAL_GetTick() - timeStart;
}
