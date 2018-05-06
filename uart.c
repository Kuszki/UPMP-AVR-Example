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

/* * * * * * * * * * * * * * * UART  OPTIONS * * * * * * * * * * * * * * * */

#define USE_INT	1		//!< Tryb pracy (1 - używaj przerwania RXC)

/* * * * * * * * * * * * * * * UART  PRIVATE * * * * * * * * * * * * * * * */

#define BUFF_SIZE	64		//!< Rozmiar bufora wejścia/wyjścia

#define step_up(x)	(x + 1) & (BUFF_SIZE - 1);

#if USE_INT == 1
volatile struct
{
	unsigned char head;		//!< Koniec danych
	unsigned char tail;		//!< Początek danych

	char data[BUFF_SIZE];	//!< Bufor na dane
}
buffer;
#endif

/* * * * * * * * * * * * * * * * UART PUBLIC * * * * * * * * * * * * * * * */

void UART_init(unsigned long baud)
{
	baud = F_CPU / (8 * baud) - 1;

#if USE_INT == 1
	buffer.head = 0;
	buffer.tail = 0;
#endif

	UBRRH = baud >> 8;
	UBRRL = baud & 0xFF;

	UCSRA = (1 << U2X);
	UCSRB = (1 << RXEN) | (1 << TXEN) | (USE_INT << RXCIE);
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
	while (!UART_ready());

#if USE_INT == 1
	buffer.tail = step_up(buffer.tail);
	return buffer.data[buffer.tail];
#else
	return UDR;
#endif
}

bool UART_ready(void)
{
#if USE_INT == 1
	return buffer.head != buffer.tail;
#else
	return UCSRA & (1 << RXC);
#endif
}

#if USE_INT == 1
ISR(USART_RXC_vect)
{
	buffer.head = step_up(buffer.head);
	buffer.data[buffer.head] = UDR;
}
#endif
