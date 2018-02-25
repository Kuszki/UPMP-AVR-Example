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

#include "adc.h"

/* * * * * * * * * * * * * * * * ADC  PUBLIC * * * * * * * * * * * * * * * */

unsigned ADC_get_value(enum ADC_MUX mux)
{
	ADMUX = (1 << REFS0)| mux;
	ADCSRA = (1 << ADEN) | (1 << ADSC);

	while (!(ADCSRA & (1 << ADIF)));

	return ADCL + (ADCH << 8);
}

double ADC_get_voltage(enum ADC_MUX mux, double ref)
{
	return ADC_get_value(mux) * ref / 10.24;
}
