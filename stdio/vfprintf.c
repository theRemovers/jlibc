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

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static char digits_lower[16] = "0123456789abcdef";
static char digits_upper[16] = "0123456789ABCDEF";

#define BUFSIZE 64

/* %[flags][width][.precision][length]specifier */
/* Where specifier is the most significant one and defines the type and the interpretation of the value of the coresponding argument: */
/* specifier	Output	Example */
/* c	Character	a */
/* d or i	Signed decimal integer	392 */
/* e	Scientific notation (mantise/exponent) using e character	3.9265e+2 */
/* E	Scientific notation (mantise/exponent) using E character	3.9265E+2 */
/* f	Decimal floating point	392.65 */
/* g	Use the shorter of %e or %f	392.65 */
/* G	Use the shorter of %E or %f	392.65 */
/* o	Signed octal	610 */
/* s	String of characters	sample */
/* u	Unsigned decimal integer	7235 */
/* x	Unsigned hexadecimal integer	7fa */
/* X	Unsigned hexadecimal integer (capital letters)	7FA */
/* p	Pointer address	B800:0000 */
/* n	Nothing printed. The argument must be a pointer to a signed int, where the number of characters written so far is stored.	 */
/* %	A % followed by another % character will write % to stdout. */

/* The tag can also contain flags, width, .precision and modifiers sub-specifiers, which are optional and follow these specifications: */

/* flags	description */
/* -	Left-justify within the given field width; Right justification is the default (see width sub-specifier). */
/* +	Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign. */
/* (space)	If no sign is going to be written, a blank space is inserted before the value. */
/* #	Used with o, x or X specifiers the value is preceeded with 0, 0x or 0X respectively for values different than zero. */
/* Used with e, E and f, it forces the written output to contain a decimal point even if no digits would follow. By default, if no digits follow, no decimal point is written. */
/* Used with g or G the result is the same as with e or E but trailing zeros are not removed. */
/* 0	Left-pads the number with zeroes (0) instead of spaces, where padding is specified (see width sub-specifier). */

/* width	description */
/* (number)	Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger. */
/* *	The width is not specified in the format string, but as an additional integer value argument preceding the argument thas has to be formatted. */

/* .precision	description */
/* .number	For integer specifiers (d, i, o, u, x, X): precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0. */
/* For e, E and f specifiers: this is the number of digits to be printed after the decimal point. */
/* For g and G specifiers: This is the maximum number of significant digits to be printed. */
/* For s: this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered. */
/* For c type: it has no effect. */
/* When no precision is specified, the default is 1. If the period is specified without an explicit value for precision, 0 is assumed. */
/* .*	The precision is not specified in the format string, but as an additional integer value argument preceding the argument thas has to be formatted. */

/* length	description */
/* h	The argument is interpreted as a short int or unsigned short int (only applies to integer specifiers: i, d, o, u, x and X). */
/* l	The argument is interpreted as a long int or unsigned long int for integer specifiers (i, d, o, u, x and X), and as a wide character or wide character string for specifiers c and s. */
/* L	The argument is interpreted as a long double (only applies to floating point specifiers: e, E, f, g and G */

int vfprintf(FILE *stream, const char *fmt, va_list ap) {
  int nb = 0;
  char c;
  char *s;
  char fill_digit;
  int nb_digit;
  char *digits = digits_lower;
  long n;
  unsigned long d = 0;
  int base = 0;
  char buffer[BUFSIZE];

  while((c = *fmt++)) {
    switch(c) {
    case '%':
      fill_digit = ' ';
      c = *fmt++;
      if(c == '0') {
	fill_digit = c;
	c = *fmt++;
      }
      nb_digit = 0;
      if(c == '*') {
	nb_digit = va_arg(ap,int);
	c = *fmt++;
      } else {
	while(c >= '0' && c <= '9') {
	  nb_digit *= 10;
	  nb_digit += (c - '0');
	  c = *fmt++;
	}
      }
      base = 0;
      switch(c) {
      case 'h':
	// short
      case 'l':
	// long
	c = *fmt++;
	break;
      }
      switch(c) {
      case 'd': 
	n = va_arg(ap,long);
	if(n < 0) {
	  d = -n;
	  nb++;
	  fputc('-',stream);
	} else {
	  d = n;
	}
	base = 10;
	break;
      case 'u':
	d = va_arg(ap,unsigned long);
	base = 10;
	break;
      case 'o':
	d = va_arg(ap,unsigned long);
	base = 8;
	break;
      case 'b':
	d = va_arg(ap,unsigned long);
	base = 2;
	break;
      case 'x':
	digits = digits_lower;
	d = va_arg(ap,unsigned long);
	base = 16;
	break;
      case 'X':
	digits = digits_upper;
	d = va_arg(ap,unsigned long);
	base = 16;
	break;
      case 'c':
	d = va_arg(ap,unsigned long);
	nb++;
	fputc(d,stream);
	break;
      case 'Q':
	s = va_arg(ap,char *);
	nb+=strlen(s)+2;
	fputc('"',stream);
	fputs(s,stream);
	fputc('"',stream);
	break;
      case 's':
	s = va_arg(ap,char *);
	nb+=strlen(s);
	fputs(s,stream);
	break;
      case '%':
	nb++;
	fputc(c,stream);
	break;
      };
      if(base > 0) {
	s=buffer+BUFSIZE;
	*--s = 0;
	while(d != 0) { 
	  *--s = digits[d % base];
	  d /= base;
	  nb++;
	  nb_digit--;
	}
	if(*s == 0) {
	  *--s = '0';
	  nb++;
	  nb_digit--;
	}
	while(--nb_digit >= 0) {
	  fputc(fill_digit,stream);
	  nb++;
	}
	fputs(s,stream);
      }
      break;
    default:
      nb++;
      fputc(c,stream);
      break;
    }
    if(c == 0) break;
  }
  return nb;
}
