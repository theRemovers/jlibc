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
 * \brief Character filters.
 */
#ifndef __CTYPE_H
#define __CTYPE_H

/** Is a letter or a digit? 

    @param c = a character

    @return TRUE if c is a letter or a digit, FALSE otherwise 

    \hideinitializer */
#define isalnum(c$) \
  ({ int _c = c$; \
     isalpha(_c) || isdigit(_c); })

/** Is a letter? 

    @param c = a character

    @return TRUE if c is a letter, FALSE otherwise 

    \hideinitializer */
#define isalpha(c$) \
  ({ int _c = c$; \
     (((_c >= 'a') && (_c <= 'z')) || ((_c >= 'A') && (_c <= 'Z'))); })

/** Is a control character? 

   @param c = a character

    @return TRUE if c is a control character, FALSE otherwise 

    \hideinitializer */
#define iscntrl(c$) \
  ({ int _c = c$; \
     (((_c >= 0) && (_c < 32)) || (_c == 127)); })

/** Is a digit? 

    @param c = a character

    @return TRUE if c is a digit, FALSE otherwise 

    \hideinitializer */
#define isdigit(c$) \
  ({ int _c = c$; \
     ((_c >= '0') && (_c <= '9')); })

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
