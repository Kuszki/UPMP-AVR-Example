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

#ifndef RTC_H_
#define RTC_H_

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util/delay.h>
#include <util/twi.h>
#include <avr/io.h>

/*! \file				rtc.h
 *  \brief			Deklaracje powiązane z modułem RTC
 *
 */

/*! \file				rtc.c
 *  \brief			Implementacja modułu RTC
 *
 */

/*!	\brief			Inicjacja komunikacji TWI
 *
 *	Ustala prescaler dla częstotliwości sygnału taktującego.
 *
 */
void RTC_init(void);

/*!	\brief			Pobranie aktualnego czasu
 * 	\param [out] time	Wskaźnik na strukturę czasu
 * 	\return			Kod błędu
 * 	\see				RTC_set_time
 *
 *	Pobiera aktualny czas i zapisuje go w wybranej strukturze. W przypadku błędu zwraca jego kod.
 *
 */
int RTC_get_time(struct tm* time);

/*!	\brief			Ustawienie aktualnego czasu
 * 	\param [in] time	Wskaźnik na strukturę czasu
 * 	\return			Kod błędu
 * 	\see				RTC_get_time
 *
 *	Zapisuje czas podany w strukturze. W przypadku błędu zwraca jego kod.
 *
 */
int RTC_set_time(const struct tm* time);

#endif /* RTC_H_ */
