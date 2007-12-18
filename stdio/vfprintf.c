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

static char buffer[128];

int vfprintf(FILE *stream, const char *fmt, va_list ap) {
  int nb = 0;
  char c;
  char *s;
  char fill_digit;
  int nb_digit;
  char *digits = digits_lower;
  long n;
  unsigned long d;
  int base = 0;

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
      while(c >= '0' && c <= '9') {
	nb_digit *= 10;
	nb_digit += (c - '0');
	c = *fmt++;
      }
      base = 0;
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
	s=buffer+128;
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
