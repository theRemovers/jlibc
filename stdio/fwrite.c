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

#include "stdio.h"

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if(stream->write != NULL) {
    return stream->write(stream,ptr,size,nmemb);
  } else {
    int i;
    char *s = (char *) ptr;
    for(i = 0; i < nmemb; i++) {
      int j;
      for(j = 0; j < size; j++) {
	if(fputc(*s++, stream) == EOF) {
	  break;
	}
      }
      if(j < size) {
	break;
      }
    }
    return i;
  }
}
