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

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

/*! \file				adc.h
 *  \brief			Deklaracje powiązane z modułem ADC
 *
 */

/*! \file				adc.c
 *  \brief			Implementacja modułu ADC
 *
 */

/*!	\brief			Wyliczenie numeru wejścia przetwornika AC
 *
 *	Wyliczenie dostępnych wejść przetwornika AC.
 *
 */
enum ADC_MUX
{
	ADC0,			//!< Wejście 1 (ADC0)
	ADC1,			//!< Wejście 2 (ADC1)
	ADC2				//!< Wejście 3 (ADC2)
};

/*!	\brief			Odczyt napięcia wejściowego przetwornika AC
 * 	\param [in] mux	Numer wejscia
 * 	\return			Wynik konwersji z zakresu <0; 1023>
 *
 *	Wykonanie pojedynczej konwersji AC dla wybranego wejścia i zwrócenie jej wyniku.
 *
 */
unsigned ADC_get_value(enum ADC_MUX mux);

/*!	\brief			Odczyt napięcia wejściowego przetwornika AC
 * 	\param [in] mux	Numer wejscia
 * 	\param [in] ref	Wartość napięcia referencyjnego
 * 	\return			Wynik konwersji z zakresu <0; ref>
 *
 *	Wykonanie pojedynczej konwersji AC dla wybranego wejścia i zwrócenie jej wyniku.
 *
 */
double ADC_get_voltage(enum ADC_MUX mux, double ref);

#endif /* ADC_H_ */
