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

#include "kbd.h"

/* * * * * * * * * * * * * * * * KBD PRIVATE * * * * * * * * * * * * * * * */

void (*KBD_actions[6])(enum KBD_ACTION) =
{
	NULL, NULL, NULL, NULL, NULL, NULL
};

static void _do_callback(char old, char new, char mask,
					void (*action)(enum KBD_ACTION))
{
	if (action != NULL)
	{
		old = old & mask;
		new = new & mask;

		if (old != new)
		{
			action(new ? RELEASED : PRESSED);
		}
	}
}

/* * * * * * * * * * * * * * * * KBD  PUBLIC * * * * * * * * * * * * * * * */

char KBD_loop(void)
{
	static char old = 0xFF;
	static char enc = 0x00;

	enc = (enc << 2) | (PINA & 0x18);
	const char new = (PIND & 0x7C) >> 2;

	for (unsigned char i = 0; i < 5; ++i)
	{
		_do_callback(old, new, 1 << i, KBD_actions[i]);
	}

	if (KBD_actions[ENC])
	{
		if (enc == 0x08 || enc == 0xF0)
		{
			KBD_actions[ENC](RIGHT);
		}

		if (enc == 0x10 || enc == 0xE8)
		{
			KBD_actions[ENC](LEFT);
		}
	}

	return old = new;
}

bool KBD_is_pressed(enum KBD_KEY key)
{
	return ~((PIND & 0x7C) >> 2 | (PINA & 0x18) << 2) & (1 << key);
}

bool KBD_is_released(enum KBD_KEY key)
{
	return ((PIND & 0x7C) >> 2 | (PINA & 0x18) << 2) & (1 << key);
}

void KBD_set_callback(enum KBD_KEY key, void (*action)(enum KBD_ACTION))
{
	KBD_actions[key] = action;
}
