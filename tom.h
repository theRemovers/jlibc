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

/** \file jagdefs.h 
 * \brief Atari Jaguar related definitions.
 */

#ifndef __TOM_H
#define __TOM_H

#include <jagtypes.h>

struct jregs {
  /* 0x00 */
  /* memory configuration */
  volatile uint16_t memcon1;
  volatile uint16_t memcon2;
  /* horizontal count */
  volatile uint16_t hc;
  /* vertical count */
  volatile uint16_t vc;
  /* light pen */
  volatile uint16_t lph;
  volatile uint16_t lpv;
  /* dummy */
  volatile uint16_t dummy1[2];
  /* 0x10 */
  /* object code */
  volatile uint16_t ob[4];
  /* dummy */
  volatile uint16_t dummy2[4];
  /* 0x20 */
  /* object list pointer */
  volatile uint32_t olp;
  /* object processor flag */
  volatile uint16_t obf;
  /* dummy */
  volatile uint16_t dummy3;
  /* video mode */
  volatile uint16_t vmode;
  /* border colour */
  volatile uint16_t bord1;
  volatile uint16_t bord2;
  /* horizontal period */
  volatile uint16_t hp;
  /* 0x30 */
  /* horizontal blanking begin */
  volatile uint16_t hbb;
  /* horizontal blanking end */
  volatile uint16_t hbe;
  /* horizontal sync */
  volatile uint16_t hs;
  /* horizontal vertical sync */
  volatile uint16_t hvs;
  /* horizontal display begin */
  volatile uint16_t hdb1;
  volatile uint16_t hdb2;
  /* horizontal display end */
  volatile uint16_t hde;
  /* vertical period */
  volatile uint16_t vp;
  /* 0x40 */
  /* vertical blanking begin */
  volatile uint16_t vbb;
  /* vertical blanking end */
  volatile uint16_t vbe;
  /* vertical sync */
  volatile uint16_t vs;
  /* vertical display begin */
  volatile uint16_t vdb;
  /* vertical display end */
  volatile uint16_t vde;
  /* vertical equalization begin */
  volatile uint16_t veb;
  /* vertical equalization end */
  volatile uint16_t vee;
  /* vertical interrupt */
  volatile uint16_t vi;
  /* 0x50 */
  /* programmable interrupt timer */
  volatile uint16_t pit[2];
  /* horizontal equalization end */
  volatile uint16_t heq;
  /* dummy */
  volatile uint16_t dummy4;
  /* background color */
  volatile uint16_t bg;
  /* dummy */
  volatile uint16_t dummy5[3+/* 0x60 */8+/* 0x70 */8+/* 0x80 */8+/* 0x90 */8+/* 0xa0 */8+/* 0xb0 */8+/* 0xc0 */8+/* 0xd0 */8];
  /* 0xe0 */
  volatile uint16_t int1;
  volatile uint16_t int2;
  volatile uint16_t dummy6[6+/* 0xf0 */+8+/* 0x100 */128+/* 0x200 */256];
  /* 0x400 */
  volatile uint16_t clut1[256];
  volatile uint16_t clut2[256];
  /* 0x800 */
  volatile uint32_t lbufA[360];
  volatile uint16_t dummy7[304];
  volatile uint32_t lbufB[360];
  volatile uint16_t dummy8[304];
  volatile uint32_t lbufC[360];
};

#define TOMREGS ((struct tomregs *)0xf00000)

#endif
