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
#ifndef __JAGDEFS_H
#define __JAGDEFS_H

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

/* Jaguar Registers */
#define BASE 0xf00000

#define JREGS ((struct jregs *)(BASE))

#define SET_SHORT_INT(value,addr) { short int v = (value); short int *a = (short int *)(addr); asm("movew %0,%1" : : "g" (v), "m" (*a) : "cc"); }
#define SET_LONG_INT(value,addr) { long v = (value); long *a = (long *)(addr); asm("movel %0,%1" : : "g" (v), "m" (*a) : "cc"); }

extern const phrase stop_object;
extern const short int a_vde;
extern const short int a_vdb;
extern const short int a_hde;
extern const short int a_hdb;
extern const short int video_width;
extern const short int video_height;
extern const short int vblPerSec;

extern void reset();

// Generic defines
#define DRAM 0
#define USERRAM 0x4000
#define ENDRAM 0x200000
#define INITSTACK (ENDRAM-4)

// CPU Registers
#define LEVEL0 0x100
#define USER0 LEVEL0

#define C_VIDENA 0x0001
#define C_GPUENA 0x0002
#define C_OPENA 0x0004
#define C_PITENA 0x0008
#define C_JERENA 0x0010

#define C_VIDCLR 0x0100
#define C_GPUCLR 0x0200
#define C_OPCLR 0x0400
#define C_PITCLR 0x0800
#define C_JERCLR 0x1000

///////////////////
// TOM Registers //
///////////////////
#define HC (BASE+4)
#define VC (BASE+6)
#define LPH (BASE+8)
#define LPV (BASE+0xa)
#define OB0 (BASE+0x10)
#define OB1 (BASE+0x12)
#define OB2 (BASE+0x14)
#define OB3 (BASE+0x16)
#define OLP (BASE+0x20)
#define OBF (BASE+0x26)
#define VMODE (BASE+0x28)
#define BORD1 (BASE+0x2a)
#define BORD2 (BASE+0x2c)
#define HDB1 (BASE+0x38)
#define HDB2 (BASE+0x3a)
#define HDE (BASE+0x3c)
#define VS (BASE+0x44)
#define VDB (BASE+0x46)
#define VDE (BASE+0x48)
#define VI (BASE+0x4e)
#define PIT0 (BASE+0x50)
#define PIT1 (BASE+0x52)
#define BG (BASE+0x58)

#define INT1 (BASE+0xe0)
#define INT2 (BASE+0xe2)

#define CLUT (BASE+0x400)

#define LBUFA (BASE+0x800)
#define LBUFB (BASE+0x1000)
#define LBUFC (BASE+0x1800)

// Video
#define VIDEN 0x0001

#define CRY16 0x0000
#define RGB24 0x0002
#define DIRECT16 0x0004
#define RGB16 0x0006

#define GENLOCK 0x0008
#define INCEN 0x0010
#define BINC 0x0020
#define CSYNC 0x0040
#define BGEN 0x0080
#define VARMOD 0x0100

#define PWIDTH1 0x0000
#define PWIDTH2 0x0200
#define PWIDTH3 0x0400
#define PWIDTH4 0x0600
#define PWIDTH5 0x0800
#define PWIDTH6 0x0a00
#define PWIDTH7 0x0c00
#define PWIDTH8 0x0e00

// GPU Registers

// Blitter Registers

#define SRCEN (0x1)
#define SRCENX (0x1 << 1)
#define DSTEN (0x1 << 3)
#define PATDSEL (0x1 << 16)
#define CMPDST (0x1 << 25)
#define BCOMPEN (0x1 << 26)
#define DCOMPEN (0x1 << 27)
#define BKGWREN (0x1 << 28)
#define SRCSHADE (0x1 << 30)

#define LFU_NAN (0x1 << 21)
#define LFU_NA (0x2 << 21)
#define LFU_AN (0x4 << 21)
#define LFU_A (0x8 << 21)

#endif
