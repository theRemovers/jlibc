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

#include "stdlib.h"
#include "malloc.h"

header *__pfree = NULL;

void *malloc(size_t size) {
  header *p, *pprev;
  size_t nsize;

  nsize = (size + sizeof(header) - 1) / sizeof(header) + 1;
  pprev = __pfree;
  for(p = pprev->s.ptr; ; pprev = p, p = p->s.ptr) {
    if(p->s.size >= nsize) {
      if(p->s.size == nsize) {
	pprev->s.ptr = p->s.ptr;
      } else {
	p->s.size -= nsize;
	p += p->s.size;
	p->s.size = nsize;
      }
      __pfree = pprev;
      return (void *)(p+1);
    }
    if(p == __pfree) {
      return NULL;
    }
  }
  return NULL;
}

#define ENDRAM 0x200000
#define ALIGN(n) (((n)+sizeof(header)) & (~(sizeof(header)-1)))
extern char BSS_E[];

void _m_init() {
  //  char *bss_end = (char *)((((unsigned long)BSS_E) + sizeof(header)) & (~(sizeof(header)-1)));
  header *bss_end = (header *)(ALIGN((unsigned long)BSS_E));
  __pfree = bss_end;
  __pfree->s.ptr = bss_end;
  __pfree->s.size = (ENDRAM-STACKSIZE-(unsigned long)bss_end) / sizeof(header);
}
