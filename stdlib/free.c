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

extern header *__pfree;

void free(void *pa) {
  header *pb , *p;
  pb = (header *)pa -1;
  for(p = __pfree; !(pb > p && pb < p->s.ptr); p = p->s.ptr) {
    if(p >= p->s.ptr && (pb > p || pb < p->s.ptr)) {
      break;
    }
  }

  if(pb + pb->s.size == p->s.ptr) {
    pb->s.size += p->s.ptr->s.size;
    pb->s.ptr = p->s.ptr->s.ptr;
  } else {
    pb->s.ptr = p->s.ptr;
  }
  if(p + p->s.size == pb) {
    p->s.size += pb->s.size;
    p->s.ptr = pb->s.ptr;
  } else {
    p->s.ptr = pb;
  }
  __pfree = p;
}
