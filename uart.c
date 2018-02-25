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

#include "uart.h"

/* * * * * * * * * * * * * * * * UART PUBLIC * * * * * * * * * * * * * * * */

void UART_init(unsigned long baud)
{
	baud = F_CPU / (8 * baud) - 1;

	UBRRH = baud >> 8;
	UBRRL = baud & 0xFF;

	UCSRA = (1 << U2X);
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << UCSZ0) | (1 << UCSZ1) | (1 << URSEL);
}

void UART_write(const char* data)
{
	while (*data) UART_putch(*data++, NULL);
}

int UART_putch(char c, FILE* f)
{
	while (!(UCSRA & (1 << UDRE)));

	UDR = c;

	return 0;
}

char UART_getch(FILE* f)
{
	while (!(UCSRA & (1 << RXC)));

	return UDR;
}
