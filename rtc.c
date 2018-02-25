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

#include "rtc.h"

/* * * * * * * * * * * * * * * * RTC PRIVATE * * * * * * * * * * * * * * * */

unsigned char BCD_convert_from(unsigned char n)
{
	return (n >> 4) * 10 + (n & 0x0F);
}

unsigned char BCD_convert_to(unsigned char n)
{
	return (( n / 10) << 4) | ((n % 10) & 0x0F);
}

int TWI_begin_write(unsigned char slave, unsigned char addr)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != TW_START) return 1;

	TWDR = slave | TW_WRITE;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != TW_MT_SLA_ACK) return 2;

	TWDR = addr;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != TW_MT_DATA_ACK) return 3;

	return 0;
}

int TWI_begin_read(unsigned char slave, unsigned char addr)
{
	int error = TWI_begin_write(slave, addr);

	if (error != 0) return error;

	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != TW_REP_START) return 4;

	TWDR = 0xD0 | TW_READ;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != TW_MR_SLA_ACK) return 5;

	return 0;
}

int TWI_put_byte(unsigned char byte)
{
	TWDR = byte;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != TW_MT_DATA_ACK) return -1;

	return 0;
}

int TWI_get_byte(unsigned char* byte, bool ack)
{
	const unsigned char status = ack ? TW_MR_DATA_ACK : TW_MR_DATA_NACK;

	TWCR = (1 << TWINT) | (1 << TWEN) | (ack ? (1 << TWEA) : 0);

	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != status) return -1;

	*byte = TWDR;

	return 0;
}

void TWI_end_transmission(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWSTO);
}

/* * * * * * * * * * * * * * * * RTC  PUBLIC * * * * * * * * * * * * * * * */

void RTC_init(void)
{
	TWBR = 0x08;
}

int RTC_get_time(struct tm* time)
{
	unsigned char data = 0;
	int error = 0;

	error = TWI_begin_read(0xD0, 0x00);

	if (error != 0) return error;
	else for (int i = 0; i < 7; ++i)
	{
		error = TWI_get_byte(&data, i != 6);

		if (error != 0) return error;
		else switch (i)
		{
			case 0:
				time->tm_sec = BCD_convert_from(data & 0x7F);
			break;
			case 1:
				time->tm_min = BCD_convert_from(data & 0x7F);
			break;
			case 2:
				time->tm_hour = BCD_convert_from(data & ((data & 0x40) ? 0x1F : 0x3F));

				if (data & 0x60) time->tm_hour *= 2;
			break;
			case 3:
				time->tm_wday = BCD_convert_from(data & 0x07) - 1;
			break;
			case 4:
				time->tm_mday = BCD_convert_from(data & 0x3F);
			break;
			case 5:
				time->tm_mon = BCD_convert_from(data & 0x1F) - 1;
			break;
			case 6:
				time->tm_year = BCD_convert_from(data & 0xFF) + 100;
			break;
		}
	}

	TWI_end_transmission();

	return 0;
}

int RTC_set_time(const struct tm* time)
{
	int error = 0;

	error = TWI_begin_write(0xD0, 0x00);

	if (error != 0) return error;
	else for (int i = 0; i < 8; ++i)
	{
		if (error != 0) return error;
		else switch (i)
		{
			case 0:
				error = TWI_put_byte(BCD_convert_to(time->tm_sec) & 0x7F);
			break;
			case 1:
				error = TWI_put_byte(BCD_convert_to(time->tm_min) & 0x7F);
			break;
			case 2:
				error = TWI_put_byte(BCD_convert_to(time->tm_hour) & 0x3F);
			break;
			case 3:
				error = TWI_put_byte(BCD_convert_to(time->tm_wday + 1) & 0x07);
			break;
			case 4:
				error = TWI_put_byte(BCD_convert_to(time->tm_mday) & 0x3F);
			break;
			case 5:
				error = TWI_put_byte(BCD_convert_to(time->tm_mon + 1) & 0x1F);
			break;
			case 6:
				error = TWI_put_byte(BCD_convert_to(time->tm_year - 100) & 0xFF);
			break;
		}
	}

	TWI_end_transmission();

	return 0;
}
