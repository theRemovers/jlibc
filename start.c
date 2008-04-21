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

#include <stdlib.h>
//extern void _m_init();

extern char BSS_E[];
#define ENDRAM 0x200000

static int sbrk_init;
static unsigned long sbrk_ptr;
static unsigned long sbrk_endram;

void *sbrk(unsigned long nb) {
  if(!sbrk_init) {
    sbrk_ptr = (((unsigned long)BSS_E+7L) & (~7L));
    sbrk_init = 1;
  }
  if(sbrk_ptr + nb > sbrk_endram) {
    return NULL;
  }
  void *ret = (void *)sbrk_ptr;
  sbrk_ptr += nb;
  return ret;
}

void __main() {
  //  _m_init();
  sbrk_init = 0;
  sbrk_endram = ENDRAM-STACKSIZE;
  srand(1);
}
