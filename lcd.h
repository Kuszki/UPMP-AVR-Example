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

#ifndef LCD_H_
#define LCD_H_

#include <string.h>
#include <stdio.h>

#include <util/delay.h>
#include <avr/io.h>

#define LCD_printf_1(...) { LCD_line1(); printf(__VA_ARGS__); }
#define LCD_printf_2(...) { LCD_line2(); printf(__VA_ARGS__); }

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
	(byte & 0x80 ? '1' : '0'), \
	(byte & 0x40 ? '1' : '0'), \
	(byte & 0x20 ? '1' : '0'), \
	(byte & 0x10 ? '1' : '0'), \
	(byte & 0x08 ? '1' : '0'), \
	(byte & 0x04 ? '1' : '0'), \
	(byte & 0x02 ? '1' : '0'), \
	(byte & 0x01 ? '1' : '0')

/*! \file				lcd.h
 *  \brief			Deklaracje powiązane z modułem LCD
 *
 */

/*! \file				lcd.c
 *  \brief			Implementacja modułu LCD
 *
 */

/*!	\brief			Inicjacja wyświetlacza
 *
 *	Inicjuje wyświetlacz ustalając 4 bity danych.
 *
 */
void LCD_init(void);

/*!	\brief			Wyczyszczenie wyświetlacza
 *
 *	Usuwa znaki z pamięci wyświetlacza.
 *
 */
void LCD_clean(void);

/*!	\brief			Ustalenie numeru linii
 *
 *	Ustawia linię 1 jako aktywne wyjście.
 *
 */
void LCD_line1(void);

/*!	\brief			Ustalenie numeru linii
 *
 *	Ustawia linię 2 jako aktywne wyjście.
 *
 */
void LCD_line2(void);

/*!	\brief			Wyświetlenie ciągu znaków
 * 	\param [in] data	Dane do wyświetlenia
 * 	\see				LCD_putch
 *
 *	Wyświetla ciąg znaków w aktywnej linii.
 *
 */
void LCD_write(const char* data);

/*!	\brief			Wyświetlenie jednego znaku
 * 	\param [in] c		Znak do wyświetlenia
 * 	\param [in] f		Wskaźnik na plik strumienia
 * 	\see				LCD_write
 *
 *	Wyświetla jeden znak w kolejnej kolumnie aktywnej linii.
 *
 */
int LCD_putch(char c, FILE* f);

#endif /* LCD_H_ */
