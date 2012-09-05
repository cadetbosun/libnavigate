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

#ifndef INCLUDE_navi_parser_h
#define INCLUDE_navi_parser_h

#include "generic.h"
#include "sentence.h"

NAVI_BEGIN_DECL

//
// Parser of IEC 61162-1 (2000-07) messages
//
// Parses the next IEC sentence up to <cr><lf> read from buffer.
// Stores the result to msg which has the maximum size of msgsize.
// The type of parsed message is stored to msgtype and the number of
// parsed characters is put to nmread.
// Returns the analysis status
//
NAVI_EXTERN(int) navi_msg_parse(char *buffer, int maxsize, int msgsize,
		void *msg, int *msgtype, int *nmread);

NAVI_END_DECL

#endif // INCLUDE_navi_parser_h
