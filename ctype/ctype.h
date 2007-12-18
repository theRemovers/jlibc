/* Jaguar C library */
/* Copyright (C) 2006 Seb/The Removers */
/* http://removers.atari.org/ */

/* This library is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU Lesser General Public */
/* License as published by the Free Software Foundation; either */
/* version 2.1 of the License, or (at your option) any later version. */

/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU */
/* Lesser General Public License for more details. */

/* You should have received a copy of the GNU Lesser General Public */
/* License along with this library; if not, write to the Free Software */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA */

/** \file ctype.h
 * \brief Character manipulation.
 */
#ifndef __CTYPE_H
#define __CTYPE_H

/** Is a letter or a digit? */
int isalnum (int c);

/** Is a letter? */
int isalpha (int c);

/** Is a control character? */
int iscntrl (int c);

/** Is a digit? */
int isdigit (int c);

/** Is a printable character different from a whitespace? */
int isgraph (int c);

/** Is lowercase letter? */
int islower (int c);

/** Is a printable character? */
int isprint (int c);

/** Is a printable character different from a whitespace and being
 * neither a letter nor a digit */
int ispunct (int c);

/** Is whitespace? */
int isspace (int c);

/** Is uppercase letter? */
int isupper (int c);

/** Is hexa digit? */
int isxdigit (int c);

/** Conversion to uppercase */
int toupper (int c);

/** Conversion to lowercase */
int tolower (int c);

#endif
