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

/** \file stdio.h
 * \brief Standard Input/Output functions.
 *
 * This part is experimental and still work in progress.  It will be
 * completed when the JagCF is released.
 */
#ifndef __STDIO_H
#define __STDIO_H

#include <stddef.h>
#include <stdarg.h>

#define EOF (-1)

#define SEEK_SET        0       /* Seek from beginning of file.  */
#define SEEK_CUR        1       /* Seek from current position.  */
#define SEEK_END        2       /* Seek from end of file.  */

typedef struct FILE {
  void *data;
  // input
  size_t (*read)(struct FILE *self, void *ptr, size_t size, size_t nmemb);
  int (*getc)(struct FILE *self);
  char *(*gets)(struct FILE *self, char *s, int size);
  // output
  size_t (*write)(struct FILE *self,const void *ptr, size_t size, size_t nmemb);
  int (*putc)(struct FILE *self,char c);
  int (*puts)(struct FILE *self,const char *s);
  // general purpose
  int (*seek)(struct FILE *self, long offset, int whence);
  long (*tell)(struct FILE *self);
  int (*flush)(struct FILE *self);
  int (*close)(struct FILE *self);
  int (*eof)(struct FILE *self);
} FILE;

/** Is end of file? */
int feof(FILE *stream);

/** Put a character in the given file */
int fputc(char c, FILE *stream);

/** Write a string in the given file */
int fputs(const char *s, FILE *stream);

/** Printf a string in the given file */
int fprintf(FILE *stream, const char *fmt, ...);
int sprintf(char *str, const char *fmt, ...);
int vfprintf(FILE *stream, const char *fmt, va_list ap);
int vsprintf(char *str, const char *fmt, va_list ap);

/** Close a file */
int fclose(FILE *stream);

/** Flush a file */
int fflush(FILE *stream);

/** Write data to a file */
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

/** Read data from a file */
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

/** Read a character from a file */
int fgetc(FILE *stream);

/** Read a string from a file */
char *fgets(char *s, int size, FILE *stream);

#endif
