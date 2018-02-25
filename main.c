/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Uruchamianie przyrządów mikroprocesorowych  --  przykładowe programy   *
 *  Copyright (C) 2018  Łukasz "Kuszki" Dróżdż  l.drozdz@openmailbox.org   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the  Free Software Foundation, either  version 3 of the  License, or   *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This  program  is  distributed  in the hope  that it will be useful,   *
 *  but WITHOUT ANY  WARRANTY;  without  even  the  implied  warranty of   *
 *  MERCHANTABILITY  or  FITNESS  FOR  A  PARTICULAR  PURPOSE.  See  the   *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have  received a copy  of the  GNU General Public License   *
 *  along with this program. If not, see http://www.gnu.org/licenses/.     *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "lcd.h"
#include "kbd.h"
#include "adc.h"
#include "rtc.h"
#include "uart.h"

void PORTS_init(void)
{
	// DDR - kierunek portu:
	//	- 0: wejścje
	//	- 1: wyjście

	// PORT - stan portu:
	//	- gdy wyjście: stan wyjścia (1/0)
	//	- gdy wejście: dla 1 tryb "pull-up"

	DDRA = 0xE0;	// wyjścia: E, R/W, R/S; wejścia: KL6, KL7, ADC0, ADC1, ADC2
	PORTA = 0x18;	// pull-up: KL6, KL7; wyjścia w stanie niskim

	DDRB = 0xBF;	// wyjścia: D1, D2, D3, D4, #SS, MOSI, SCK; wejścia: MISO
	PORTB = 0x00;	// bez pull-up; wyjścia w stanie niskim

	DDRC = 0xDF;	// wyjścia: LED2, LED3, TDO, TMS, TCK, SDA, SCL; wejścia: TDI
	PORTC = 0x03;	// bez pull-up; wyjścia SDA, SCL w stanie wysokim

	DDRD = 0x82;	// wyjścia: LED1, TXD; wejścia: RXD, KL1, KL2, KL3, KL4, KL5
	PORTD = 0x7F;	// pull-up: KL1, KL2, KL3, KL4, KL5, RXD; TDX w stanie wysokim
}

int main (void)
{
	PORTS_init();
	UART_init(9600);

	LCD_init();
	RTC_init();

	fdevopen(LCD_putch, NULL);

	struct tm time;

	while (1)
	{
		RTC_get_time(&time);

		LCD_printf_1("%02u.%02u.%04u", time.tm_mday, time.tm_mon + 1, time.tm_year + 1900);
		LCD_printf_2("%02u.%02u.%02u", time.tm_hour, time.tm_min, time.tm_sec);

		_delay_ms(250);
	}
}
