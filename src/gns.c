/*
 * gns.c - generator and parser of GNS message
 *
 * Copyright (C) 2012 I. S. Gorbunov <igor.genius at gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libnavigate/gns.h>
#include <libnavigate/common.h>

#include <navigate.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes GNS sentence structure with default values
navierr_status_t navi_init_gns(struct gns_t *msg)
{
	size_t i;

	assert(msg != NULL);

	navi_init_utc(&msg->utc);
	navi_init_position(&msg->fix);
	for (i = 0; i < GNS_MODEINDICATOR_SIZE; i++)
		msg->mi[i] = navi_DataNotValid;
	msg->nmsatellites = -1;
	navi_init_number(&msg->hdop);
	navi_init_number(&msg->antaltitude);
	navi_init_number(&msg->geoidalsep);
	msg->diffdata_age = -1;
	msg->station_id = -1;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates GNS message
navierr_status_t navi_create_gns(const struct gns_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	char utc[32], fix[64], mi[3], totalsats[3], hdop[32], antalt[32],
		geoidsep[32], ddage[32], drsid[32];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc));
	msglength += navi_print_position_fix(&msg->fix, fix, sizeof(fix));
	msglength += navi_print_miarray(msg->mi,
		sizeof(msg->mi) / sizeof(msg->mi[0]), mi);
	msglength += snprintf(totalsats, sizeof(totalsats),
		(msg->nmsatellites == -1) ? "" : "%02u", msg->nmsatellites);
	msglength += navi_print_number(msg->hdop, hdop, sizeof(hdop));
	msglength += navi_print_number(msg->antaltitude, antalt, sizeof(antalt));
	msglength += navi_print_number(msg->geoidalsep, geoidsep, sizeof(geoidsep));
	msglength += navi_print_number(msg->diffdata_age, ddage, sizeof(ddage));
	msglength += snprintf(drsid, sizeof(drsid),
		(msg->station_id == -1) ? "" : "%i", msg->station_id);

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s,%s",
		utc, fix, mi, totalsats, hdop, antalt, geoidsep, ddage, drsid);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses GNS message
navierr_status_t navi_parse_gns(struct gns_t *msg, char *buffer)
{
	size_t i = 0, j, nmread;
	double d;

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_position_fix(buffer + i, &msg->fix, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	j = sizeof(msg->mi) / sizeof(msg->mi[0]);
	if (navi_parse_miarray(buffer + i, msg->mi, &j, &nmread) != navi_Ok)
	{
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->nmsatellites = (int)round(d);
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->hdop, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->antaltitude, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->geoidalsep, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->diffdata_age = (int)round(d);
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->station_id = (int)round(d);
	}

	return navi_Ok;
}

#endif // NO_PARSER
