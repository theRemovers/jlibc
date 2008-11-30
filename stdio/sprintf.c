#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static int putc(FILE *stream, int c) {
  *((char*)stream->data++) = c;
  return (int)c;
}

static int puts(FILE *stream, const char *s) {
  int n = strlen(s);
  bcopy(s,(char*)stream->data,n);
  stream->data = (char *)stream->data + n;
  return n;
}

static size_t write(FILE *stream, const  void  *ptr,  size_t  size,  size_t  nmemb) {
  return EOF;
}

static int eof(FILE *stream) {
  return 0;
}

int sprintf(char *str,const char *fmt, ...) {
  if(str == NULL) return -1;
  FILE *fp = calloc(1, sizeof(FILE));
  fp->data = str;
  fp->eof = eof;
  fp->putc = putc;
  fp->puts = puts;
  fp->write = write;
  va_list ap;
  va_start(ap,fmt);
  int nb = vfprintf(fp,fmt,ap);
  va_end(ap);
  free(fp);
  *(str + nb) = 0;
  return nb;
}
