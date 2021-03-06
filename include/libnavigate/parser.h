/*
 * parser.h - interface to IEC message parser
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

/*! @file parser.h
 *  @brief Declares API-calls for parsing messages.
 *
 *  Contains declarations for the main parser function and some helpful
 *  utilities for use in parsing of messages.
 */

#ifndef INCLUDE_navi_parser_h
#define INCLUDE_navi_parser_h

#include "sentence.h"

NAVI_BEGIN_DECL

//! @brief Parser of IEC 61162-1 (2000-07) messages
//!
//! Parses the next IEC sentence up to [cr][lf] read from buffer.
//! Stores the result to msg which has the maximum size of msgsize.
//! The type of parsed message is stored to type and the number of
//! parsed characters is put to nmread.
//! If the parsed sentence is an approved sentence, the approved_field_t
//! structure is put ath beginning of msg, and the message body is put
//! after that structure.
//! @return the analysis status
NAVI_EXTERN(navierr_status_t) navi_parse_msg(char *buffer, size_t maxsize,
	size_t msgsize, navi_addrfield_t *type, void *msg, size_t *nmread);

//! @brief Parses offset field in the form of 'x.x,a | ,'.
//!
//! The field must end with ',' or '*'
//! @param[in] buffer pointer to the first byte of field
//! @param[out] offset pointer to structure where the result is stored
//! @param[out] nmread pointer to variable where the number of read bytes is stored
//! @return 0 on success, or navi_Error if it's null or an error occured. Call
//! navierr_get_last() to check the error
NAVI_EXTERN(navierr_status_t) navi_parse_offset(char *buffer,
	struct navi_offset_t *offset, size_t *nmread);

//! @brief Parses position fix in the form of 'llll.ll,a,yyyyy.yy,a | ,,,'.
//!
//! The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_position_fix(char *buffer,
	struct navi_position_t *fix, size_t *nmread);

//! @brief Parses UTC time in the form of 'hhmmss.ss' of null field.
//!
//! The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_utc(char *buffer, struct navi_utc_t *utc, size_t *nmread);

//! @brief Parses status in the form of 'A | V'. Shall not be null field.
//!
//! The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_status(char *buffer, navi_status_t *status, size_t *nmread);

//! @brief Parses GSA sentence 2D/3D switching mode in the form of 'M | A'.
//!
//! The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_gsamode(char *buffer, navi_gsaswitchmode_t *mode, size_t *nmread);

//! @brief Parses mode indicator in the form of 'A | D | E | M | S | N'.
//!
//! Shall not be null field. The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_modeindicator(char *buffer, navi_modeindicator_t *mi, size_t *nmread);

//! @brief Parses variable numbers in the form of '[+|-]x[.x]'.
//!
//! May be null field. The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_number(char *buffer, double *parsed, size_t *nmread);

//! @brief Parses fixed length hexadecimal field, MSB on the left: 'hh-'.
//!
//! May be null field. The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_hexfield(char *buffer, int fieldwidth,
	char bytes[], size_t *nmread);

//! @brief Parses fixed length decimal field: 'xx-'.
//!
//! May be null field. The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_decfield(char *buffer, int fieldwidth,
	char bytes[], size_t *nmread);

//! @brief Parses datum field in the form of 'ccc'
//!
//! May be null field. The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_datum(char *buffer, navi_datum_t *datum, size_t *nmread);

//! @brief Parses datum subdivision code field in the form of 'a'.
//!
//! May be null field. The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_datumsub(char *buffer, navi_datum_subdivision_t *datumsub, size_t *nmread);

//! @brief Parses mode indicator array in the form of 'c--c'.
//!
//! May not be null field. The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_miarray(char *buffer, navi_modeindicator_t mi[], size_t *misize, size_t *nmread);

//! @brief Parses date in the form of 'ddmmyy | ddmmyyyy'
//!
//! May be null field. The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_date(char *buffer, struct navi_date_t *date, size_t *nmread);

//! @brief Parses local zone in the form of '[+|-]dd,dd'.
//!
//! May be null field. The field must end with ',' or '*'
//! @return 0 if parsed successfully, or navi_Error in the case of an error
NAVI_EXTERN(navierr_status_t) navi_parse_localzone(char *buffer, int *offset, size_t *nmread);

//! @brief Extracts the latitude and longitude from the navi_position_t structure and
//! converts them to radians.
//!
//! Output latitude is in the range of [-pi, +pi].
//! Output longitude in the range of [0, +2pi].
NAVI_EXTERN(navierr_status_t) navi_get_position(const struct navi_position_t *in,
	double *latitude, double *longitude);

//! @brief Parses a buffer with valid characters from the given string,
//! translating triples '^xx' to reserved characters.
//!
//! @return navi_Error, if the conversion is not possible
NAVI_EXTERN(navierr_status_t) navi_parse_character_field(const char *from,
	char *to, size_t maxsize, size_t *nmread);

NAVI_END_DECL

#endif // INCLUDE_navi_parser_h
