/*
 * generator.h - interface to IEC message generator
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

#ifndef INCLUDE_navi_generator_h
#define INCLUDE_navi_generator_h

#include "generic.h"
#include "sentence.h"

NAVI_BEGIN_DECL

//
// Generator for IEC 61162-1 (2000-07) messages
//
// Generates IEC sentence by its description given by type and msg.
// Stores the result to buffer which has the maximum size of maxsize.
// The number of stored characters is stored to nmwritten.
// Returns the status of sentence compilation
//
NAVI_EXTERN(int) navi_msg_create(int type, void *msg, char *buffer,
		int maxsize, int *nmwritten);

NAVI_END_DECL

#endif // INCLUDE_navi_generator_h
