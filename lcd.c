/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Uruchamianie przyrządów mikroprocesorowych - przykładowe programy      *
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

/* * * * * * * * * * * * * * * * LCD PRIVATE * * * * * * * * * * * * * * * */

#define sbi(sfr, bit)	(_SFR_BYTE(sfr) |= _BV(bit))				//!< Ustaw bit w rejestrze
#define cbi(sfr, bit)	(_SFR_BYTE(sfr) &= ~_BV(bit))				//!< Skasuj bit w rejestrze
#define put_data(data)	(PORTB = (PORTB & 0xF0) | (data & 0x0F))	//!< Wystaw dane D4..D7

static void _enable_a(void)
{
	cbi(PORTA, 7);
	sbi(PORTA, 7);

	_delay_us(5);

	cbi(PORTA, 7);

	_delay_us(55);
}

static void _enable_l(void)
{
	cbi(PORTA, 7);
	sbi(PORTA, 7);

	_delay_us(5);

	cbi(PORTA, 7);

	_delay_ms(1);
}

static void _enable_s(void)
{
	cbi(PORTA, 7);
	sbi(PORTA, 7);

	_delay_us(5);

	cbi(PORTA, 7);

	_delay_us(1);
}

static void _put_data(char data)
{
	put_data(data >> 4);
	_enable_s();

	put_data(data & 0x0F);
	_enable_a();
}

/* * * * * * * * * * * * * * * * LCD  PUBLIC * * * * * * * * * * * * * * * */

void LCD_init(void)
{
	cbi(PORTA, 5); // dane = instruklcje
	cbi(PORTA, 6); // akcja = zapis

	_delay_ms(50);

	put_data(0x03);
	_enable_l();

	_delay_ms(15);

	put_data(0x03);
	_enable_l();

	_delay_ms(5);

	put_data(0x03);
	_enable_l();

	_delay_ms(5);

	put_data(0x02);
	_enable_l();

	_delay_ms(5);

	_put_data(0x28);
	_put_data(0x0C);
	_put_data(0x01);
	_put_data(0x06);
}

void LCD_clean(void)
{
	cbi(PORTA, 5); // dane = instruklcje
	cbi(PORTA, 6); // akcja = zapis

	_put_data(0x01);

	_delay_us(2200);
}

void LCD_line1(void)
{
	cbi(PORTA, 5); // dane = instruklcje
	cbi(PORTA, 6); // akcja = zapis

	_put_data(0x80);
}

void LCD_line2(void)
{
	cbi(PORTA, 5); // dane = instruklcje
	cbi(PORTA, 6); // akcja = zapis

	_put_data(0xC0);
}

void LCD_write(const char* data)
{
	while (*data) LCD_putch(*data++, NULL);
}

int LCD_putch(char c, FILE* f)
{
	sbi(PORTA, 5); // dane = znaki
	cbi(PORTA, 6); // akcja = zapis

	_put_data(c);

	return 0;
}
