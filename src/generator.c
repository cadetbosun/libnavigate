/*
 * generator.c - IEC messages generation utilities
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

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <locale.h>

#include <libnavigate/config.h>
#include <libnavigate/generator.h>
#include <libnavigate/common.h>

#ifndef NO_GENERATOR

#include <libnavigate/aam.h>
#include <libnavigate/ack.h>
#include <libnavigate/alm.h>
#include <libnavigate/alr.h>
#include <libnavigate/apb.h>
#include <libnavigate/bec.h>
#include <libnavigate/bod.h>
#include <libnavigate/bwc.h>
#include <libnavigate/bwr.h>
#include <libnavigate/bww.h>
#include <libnavigate/dtm.h>
#include <libnavigate/gbs.h>
#include <libnavigate/gga.h>
#include <libnavigate/gll.h>
#include <libnavigate/gns.h>
#include <libnavigate/grs.h>
#include <libnavigate/gsa.h>
#include <libnavigate/gst.h>
#include <libnavigate/gsv.h>
#include <libnavigate/mla.h>
#include <libnavigate/rmc.h>
#include <libnavigate/txt.h>
#include <libnavigate/vtg.h>
#include <libnavigate/zda.h>

#include <libnavigate/proprietarymsg.h>

#endif // NO_GENERATOR

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Talker IDs list
extern const char *navi_tidlist[];

//
// Approved sentence formatters list
extern const char *navi_fmtlist[];

//
// Creates approved sentence
static navierr_status_t navi_create_approved(struct approved_field_t *address,
	const void *msg, char *buffer, size_t maxsize, size_t *nmwritten);

//
// Creates query sentence
static navierr_status_t navi_create_query(struct query_field_t *address,
	navi_approved_fmt_t msg, char *buffer, size_t maxsize, size_t *nmwritten);

//
// IEC message generator
//
navierr_status_t navi_create_msg(navi_addrfield_t type, const void *address,
	const void *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{

#ifndef NO_GENERATOR

	assert(msg != NULL);
	assert(buffer != NULL);
	assert(nmwritten != NULL);

	switch (type)
	{
	case navi_af_Approved:
		return navi_create_approved((struct approved_field_t *)address,
			msg, buffer, maxsize, nmwritten);
	case navi_af_Query:
		return navi_create_query((struct query_field_t *)address,
			*(navi_approved_fmt_t *)msg, buffer, maxsize, nmwritten);
	case navi_af_Proprietary:
		return navi_create_proprietary(msg, buffer, maxsize, nmwritten);
	case navi_af_Unknown:
	default:
		navierr_set_last(navi_InvalidParameter);
		return navi_Error;
	}

#else

	navierr_set_last(navi_NotImplemented);
	return navi_Error;

#endif // NO_GENERATOR

}

//
// Creates approved sentence
static navierr_status_t navi_create_approved(struct approved_field_t *address,
	const void *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	const char *tid = NULL, *sfmt = NULL;
	char msgbody[NAVI_SENTENCE_MAXSIZE + 1], csstr[3];

	size_t msglen = 0;

	switch (address->afmt)
	{
	case navi_AAM:
		if (navi_create_aam((const struct aam_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_ACK:
		if (navi_create_ack((const struct ack_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_ALM:
		if (navi_create_alm((const struct alm_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_ALR:
		if (navi_create_alr((const struct alr_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_APB:
		if (navi_create_apb((const struct apb_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_BEC:
		if (navi_create_bec((const struct bec_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_BOD:
		if (navi_create_bod((const struct bod_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_BWC:
		if (navi_create_bwc((const struct bwc_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_BWR:
		if (navi_create_bwr((const struct bwr_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_BWW:
		if (navi_create_bww((const struct bww_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_DBT:
	case navi_DCN:
	case navi_DPT:
	case navi_DSC:
	case navi_DSE:
	case navi_DSI:
	case navi_DSR:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_DTM:
		if (navi_create_dtm((const struct dtm_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_FSI:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_GBS:
		if (navi_create_gbs((const struct gbs_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_GGA:
		if (navi_create_gga((const struct gga_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_GLC:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_GLL:
		if (navi_create_gll((const struct gll_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_GNS:
		if (navi_create_gns((const struct gns_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_GRS:
		if (navi_create_grs((const struct grs_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_GSA:
		if (navi_create_gsa((const struct gsa_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_GST:
		if (navi_create_gst((const struct gst_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_GSV:
		if (navi_create_gsv((const struct gsv_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_HDG:
	case navi_HDT:
	case navi_HMR:
	case navi_HMS:
	case navi_HSC:
	case navi_HTC:
	case navi_HTD:
	case navi_LCD:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_MLA:
		if (navi_create_mla((const struct mla_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_MSK:
	case navi_MSS:
	case navi_MTW:
	case navi_MWD:
	case navi_MWV:
	case navi_OSD:
	case navi_RMA:
	case navi_RMB:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_RMC:
		if (navi_create_rmc((const struct rmc_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_ROT:
	case navi_RPM:
	case navi_RSA:
	case navi_RSD:
	case navi_RTE:
	case navi_SFI:
	case navi_STN:
	case navi_TLB:
	case navi_TLL:
	case navi_TTM:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_TXT:
		if (navi_create_txt((const struct txt_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_VBW:
	case navi_VDR:
	case navi_VHW:
	case navi_VLW:
	case navi_VPW:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_VTG:
		if (navi_create_vtg((const struct vtg_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_WCV:
	case navi_WNC:
	case navi_WPL:
	case navi_XDR:
	case navi_XTE:
	case navi_XTR:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_ZDA:
		if (navi_create_zda((const struct zda_t *)msg, msgbody,
			sizeof(msgbody), &msglen) != navi_Ok)
		{
			return navi_Error;
		}
		break;
	case navi_ZDL:
	case navi_ZFO:
	case navi_ZTG:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	default:
		navierr_set_last(navi_MsgNotSupported);
		return navi_Error;
	}

	if (msglen + 12 > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	if (msglen + 12 > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	tid = navi_talkerid_str(address->tid);
	sfmt = navi_sentencefmt_str(address->afmt);

	msglen = snprintf(buffer, maxsize, "$%s%s,%s*", tid, sfmt, msgbody);
	if (navi_checksum(buffer, msglen, csstr, NULL) != navi_Ok)
		return navi_Error;
	strcat(buffer, csstr);
	strcat(buffer, "\r\n");

	*nmwritten = msglen + 4;

	return navi_Ok;
}

//
// Creates query sentence
static navierr_status_t navi_create_query(struct query_field_t *address,
	navi_approved_fmt_t msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	const char *from_tid = NULL, *to_tid = NULL;
	const char *requested_fmt = NULL;
	char csstr[3];

	size_t msglen = 0;

	from_tid = navi_talkerid_str(address->from);
	to_tid = navi_talkerid_str(address->to);

	requested_fmt = navi_sentencefmt_str(msg);

	msglen = snprintf(buffer, maxsize, "$%s%sQ,%s*", from_tid, to_tid, requested_fmt);
	if (navi_checksum(buffer, msglen, csstr, NULL) != navi_Ok)
		return navi_Error;
	strcat(buffer, csstr);
	strcat(buffer, "\r\n");

	*nmwritten = msglen + 4;

	return navi_Ok;
}

//
// Returns the string representation of geodetic datum
const char *navi_datum_str(navi_datum_t datum)
{
	switch (datum)
	{
	case navi_WGS84:
		return "W84";
	case navi_WGS72:
		return "W72";
	case navi_SGS85:
		return "S85";
	case navi_PE90:
		return "P90";
	case navi_UserDefined:
		return "999";
	case navi_datum_NULL:
		return "";
	default:
		return NULL;
	}
}

//
// Returns the string representation of geodetic datum subdivision code
const char *navi_datumsubdiv_str(navi_datum_subdivision_t datumsub)
{
	switch (datumsub)
	{
	case navi_datumsub_NULL:
		return "";
	default:
		return NULL;
	}
}

//
// Returns the offset or position fix sign
const char *navi_fixsign_str(navi_offset_sign_t fixsign)
{
	switch (fixsign)
	{
	case navi_North:
		return "N";
	case navi_South:
		return "S";
	case navi_East:
		return "E";
	case navi_West:
		return "W";
	case navi_Left:
		return "L";
	case navi_Right:
		return "R";
	case navi_True:
		return "T";
	case navi_Magnetic:
		return "M";
	case navi_offset_NULL:
		return "";
	default:
		return NULL;
	}
}

//
// navi_status_str
//
const char *navi_status_str(navi_status_t status)
{
	switch (status)
	{
	case navi_status_A:
		return "A";
	case navi_status_V:
		return "V";
	case navi_status_NULL:
		return "";
	default:
		return NULL;
	}
}

//
// navi_modeindicator_str
//
const char *navi_modeindicator_str(navi_modeindicator_t mi)
{
	switch (mi)
	{
	case navi_Autonomous:
		return "A";
	case navi_Differential:
		return "D";
	case navi_Estimated:
		return "E";
	case navi_ManualInput:
		return "M";
	case navi_Simulator:
		return "S";
	case navi_DataNotValid:
		return "N";
	default:
		return NULL;
	}
}

//
// navi_modeindicator_extended_str
//
const char *navi_modeindicator_extended_str(navi_modeindicator_t mi)
{
	switch (mi)
	{
	case navi_Autonomous:
		return "A";
	case navi_Differential:
		return "D";
	case navi_Estimated:
		return "E";
	case navi_ManualInput:
		return "M";
	case navi_Simulator:
		return "S";
	case navi_DataNotValid:
		return "N";
	case navi_Precise:
		return "P";
	case navi_RTKinematic:
		return "R";
	case navi_FloatRTK:
		return "F";
	default:
		return NULL;
	}
}

//
// Returns the GSA 2D/3D switching mode
const char *navi_gsamode_str(navi_gsaswitchmode_t mode)
{
	switch (mode)
	{
	case navi_gsa_Manual:
		return "M";
	case navi_gsa_Automatic:
		return "A";
	case navi_gsa_NULL:
		return "";
	default:
		return NULL;
	}
}

//
// Prints offset 'x.x,a', or null fields
size_t navi_print_offset(const struct navi_offset_t *offset, char *buffer, size_t maxsize)
{
	size_t nmwritten = 0;

	assert(offset != NULL);
	assert(buffer != NULL);
	assert(maxsize > 0);

	if (navi_check_validity_offset(offset) == navi_Ok)
	{
		const char *s;

		nmwritten += navi_print_number(offset->offset, buffer, maxsize);

		(void)strncat(buffer, ",", maxsize);
		nmwritten++;

		nmwritten += strlen(s = navi_fixsign_str(offset->sign));
		(void)strncat(buffer, s, maxsize);
	}
	else
	{
		nmwritten += snprintf(buffer, maxsize, ",");
	}

	return nmwritten;
}

//
// Prints position fix 'llll.ll,a,yyyyy.yy,a', or null fields
size_t navi_print_position_fix(const struct navi_position_t *fix, char *buffer,
	size_t maxsize)
{
	size_t nmwritten = 0;

	assert(fix != NULL);
	assert(buffer != NULL);

	if (navi_check_validity_position(fix) == navi_Ok)
	{
		int precision;
		double degrees, fraction;

		const char *s;
		char *oldlocale = setlocale(LC_NUMERIC, NULL);
		(void)setlocale(LC_NUMERIC, "POSIX");

		precision = naviconf_get_presicion();

		// extract and print latitude
		fraction = modf(fix->latitude.offset, &degrees);
		degrees = degrees * 100.0;
		fraction = fraction * 60.0;
		fraction = fraction + degrees;

		nmwritten += snprintf(buffer + nmwritten, maxsize, "%0*.*f",
			precision + 5, precision, fraction);
		nmwritten = remove_trailing_zeroes(buffer, nmwritten);

		(void)strncat(buffer, ",", maxsize);
		nmwritten++;

		nmwritten += strlen(s = navi_fixsign_str(fix->latitude.sign));
		(void)strncat(buffer, s, maxsize);

		(void)strncat(buffer, ",", maxsize);
		nmwritten++;

		// extract and print longitude
		fraction = modf(fix->longitude.offset, &degrees);
		degrees = degrees * 100.0;
		fraction = fraction * 60.0;
		fraction = fraction + degrees;

		nmwritten += snprintf(buffer + nmwritten, maxsize, "%0*.*f",
			precision + 6, precision, fraction);
		nmwritten = remove_trailing_zeroes(buffer, nmwritten);

		(void)strncat(buffer, ",", maxsize);
		nmwritten++;

		nmwritten += strlen(s = navi_fixsign_str(fix->longitude.sign));
		(void)strncat(buffer, s, maxsize);

		setlocale(LC_NUMERIC, oldlocale);
	}
	else
	{
		nmwritten += snprintf(buffer, maxsize, ",,,");
	}

	return nmwritten;
}

//
// Prints variable numbers
size_t navi_print_number(double value, char *buffer, size_t maxsize)
{
	if (navi_check_validity_number(value) == navi_Ok)
	{
		int result, precision;
		char *oldlocale = setlocale(LC_NUMERIC, NULL);
		setlocale(LC_NUMERIC, "POSIX");

		precision = naviconf_get_presicion();
		result = snprintf(buffer, maxsize, "%.*f", precision, value);

		setlocale(LC_NUMERIC, oldlocale);
		return remove_trailing_zeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

//
// Prints UTC time
size_t navi_print_utc(const struct navi_utc_t *utc, char *buffer, size_t maxsize)
{
	assert(utc != NULL);

	if (navi_check_validity_utc(utc) == navi_Ok)
	{
		int result, precision;
		char *oldlocale = setlocale(LC_NUMERIC, NULL);
		setlocale(LC_NUMERIC, "POSIX");

		precision = naviconf_get_presicion();
		result = snprintf(buffer, maxsize, "%02u%02u%0*.*f",
			utc->hour % 24, utc->min % 60, precision + 3, precision, utc->sec);

		setlocale(LC_NUMERIC, oldlocale);
		return remove_trailing_zeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

//
// navi_print_miarray
//
size_t navi_print_miarray(const navi_modeindicator_t mi[], int miquant, char *buffer)
{
	int i;
	const char *mistr;

	assert(buffer != NULL);

	strcpy(buffer, "");
	for (i = 0; i < miquant; i++)
	{
		mistr = navi_modeindicator_extended_str(mi[i]);
		if (strlen(mistr) == 0)
		{
			navierr_set_last(navi_InvalidParameter);
			return 0;
		}
		strcat(buffer, mistr);
	}

	return i;
}

//
// navi_sentencefmt_str
//
const char *navi_sentencefmt_str(navi_approved_fmt_t fmt)
{
	assert((fmt >= navi_AAM) && (fmt <= navi_ZTG));
	return navi_fmtlist[fmt];
}

//
//	navi_create_talkerid
//
const char *navi_talkerid_str(navi_talkerid_t tid)
{
	assert((tid >= navi_AG) && (tid <= navi_WI));
	return navi_tidlist[tid];
}

//
// navi_print_numfield
//
size_t navi_print_fixedfield(const char bytes[], int fieldwidth, int radix,
	char *buffer, size_t maxsize)
{
	int i;
	char str[4];

	assert(buffer != NULL);

	(void)strncpy(buffer, "", maxsize);

	for (i = 0; i < fieldwidth; i++)
	{
		switch (radix)
		{
		case 10:
			snprintf(str, sizeof(str), "%d", bytes[i]);
			break;
		case 16:
			snprintf(str, sizeof(str), "%x", bytes[i]);
			break;
		default:
			snprintf(str, sizeof(str), "%c", bytes[i]);
			break;
		}
		(void)strncat(buffer, str, maxsize);
	}

	return i;
}

//
// navi_print_hexfield
//
size_t navi_print_hexfield(const char bytes[], int fieldwidth,
	char *buffer, size_t maxsize)
{
	return navi_print_fixedfield(bytes, fieldwidth, 16, buffer, maxsize);
}

//
// navi_print_decfield
//
size_t navi_print_decfield(const char bytes[], int fieldwidth,
	char *buffer, size_t maxsize)
{
	return navi_print_fixedfield(bytes, fieldwidth, 10, buffer, maxsize);
}

//
// navi_print_character_field
//
navierr_status_t navi_print_character_field(const char *from, char *to, size_t maxsize)
{
	size_t i, j, srclen;
	char bytes[2];

	assert(from != NULL);
	assert(to != NULL);
	assert(maxsize > 0);

	srclen = strlen(from);

	for (i = j = 0; i < srclen; i++)
	{
		switch (navi_get_character_type(from[i]))
		{
		case navi_char_Valid:
			if (j >= maxsize - 1)
				return navi_Error;

			to[j++] = from[i];
			break;
		default:
			if (j >= maxsize - 4)
				return navi_Error;

			navi_split_integer(from[i], bytes, 2, 16);

			to[j++] = '^';
			to[j++] = bytes[0] < 10 ? bytes[0] + '0' : bytes[0] - 10 + 'A';
			to[j++] = bytes[1] < 10 ? bytes[1] + '0' : bytes[1] - 10 + 'A';
			break;
		}
	}

	to[j] = '\0';

	return navi_Ok;
}
