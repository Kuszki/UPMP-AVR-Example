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

#ifndef UART_H_
#define UART_H_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/io.h>

/*! \file				uart.h
 *  \brief			Deklaracje powiązane z modułem UART
 *
 */

/*! \file				uart.c
 *  \brief			Implementacja modułu UART
 *
 */

/*!	\brief			Inicjacja interfejsu UART
 * 	\param [in] baud	Predkość transmisji w bps
 *
 *	Inicjacja interfejsu UART (8 bitów danych, 1 bit stopu, brak bitu parzystości).
 *
 */
void UART_init(unsigned long baud);

/*!	\brief			Wysłanie ciągu znaków
 * 	\param [in] data	Dane do wyświetlenia
 * 	\see				UART_putch
 *
 *	Wysyła ciąg znaków za pomocą UART.
 *
 */
void UART_write(const char* data);

/*!	\brief			Wysłanie jednego znaku
 * 	\param [in] c		Znak do wysłania
 * 	\param [in] f		Wskaźnik na plik strumienia
 * 	\see				UART_write
 *
 *	Wysyła jeden znak za pomocą UART.
 *
 */
int UART_putch(char c, FILE* f);

/*!	\brief			Pobranie jednego znaku
 * 	\param [in] f		Wskaźnik na plik strumienia
 * 	\return			Pobrany znak
 *
 *	Czeka na możliwość odbioru danych i pobiera jeden znak za pomocą UART.
 *
 */
char UART_getch(FILE* f);

/*!	\brief			Sprawdzenie dostępności zbuforowanych danych
 * 	\return			Prawda, gdy zbuforowano jakiekolwiek dane
 *
 *	Sprawdza, czy w buforze zapisano dane. Działa tylko w trybie pracy z przerwaniem.
 *
 */
bool UART_ready(void);

#endif /* UART_H_ */
