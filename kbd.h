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

#ifndef KBD_H_
#define KBD_H_

#include <stdbool.h>
#include <string.h>

#include <avr/io.h>

/*! \file				kbd.h
 *  \brief			Deklaracje powiązane z modułem klawiatury
 *
 */

/*! \file				kbd.c
 *  \brief			Implementacja modułu klawiatury
 *
 */

/*!	\brief			Wyliczenie numeru klawisza
 *
 *	Wyliczenie dostępnych klawiszy.
 *
 */
enum KBD_KEY
{
	KL1,				//!< Klawisz 1 (SW1)
	KL2,				//!< Klawisz 2 (SW2)
	KL3,				//!< Klawisz 3 (EnkoderSW)
	KL4,				//!< Klawisz 4 (SW3)
	KL5,				//!< Klawisz 5 (SW4)
	ENC				//!< Enkoder (ruch w prawo, ruch w lewo)
};

/*!	\brief			Wyliczenie akcji klawisza
 *
 *	Wyliczenie dostępnych akcji powodowanych przez klawisze.
 *
 */
enum KBD_ACTION
{
	PRESSED,			//!< Wciśnięto klawisz
	RELEASED,			//!< Puszczono klawisz
	LEFT,			//!< Ruch enkodera w lewo
	RIGHT			//!< Ruch enkodera w prawo
};

/*!	\brief			Pętla obsługi klawiatury
 *
 *	Obsługa zmiany stanów wejść związanych z klawiaturą. Do uruchamiania w pętli głównej.
 *
 */
char KBD_loop(void);

/*!	\brief			Sprawdzenie stanu przycisku
 * 	\param [in] key	Numer przycisku
 * 	\return			`true` jeżeli wciśnięto przycisk
 *
 *	Sprawdzenie stanu wciśnięcia przycisku niezależne od petli obsługi klawiatury.
 *
 */
bool KBD_is_pressed(enum KBD_KEY key);

/*!	\brief			Sprawdzenie stanu przycisku
 * 	\param [in] key	Numer przycisku
 * 	\return			`true` jeżeli nie wciśnięto przycisku
 *
 *	Sprawdzenie stanu wciśnięcia przycisku niezależne od petli obsługi klawiatury.
 *
 */
bool KBD_is_released(enum KBD_KEY key);

/*!	\brief			ustalenie funkcji zwrotnej przycisku
 * 	\param [in] key	Numer przycisku
 * 	\param [in] action	Funkcja zwrotna
 * 	\see				KBD_loop
 *
 *	Ustalenie akcji dla zmiany stanu przycisku wykrywanej podczas pętli obsługi klawiatury.
 *
 */
void KBD_set_callback(enum KBD_KEY key, void (*action)(enum KBD_ACTION));

#endif /* KBD_H_ */
