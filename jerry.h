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

/** \file jerry.h
 * \brief JERRY hardware registers
 */

#ifndef __JERRY_H
#define __JERRY_H

#include <jagtypes.h>

struct jerry_registers {
  /* 0x00 */
  volatile uint16_t jpit1_wo[2];
  volatile uint16_t jpit2_wo[2];
  volatile uint16_t dummy1[4];
  /* 0x10 */
  volatile uint16_t clk1;
  volatile uint16_t clk2;
  volatile uint16_t clk3;
  volatile uint16_t dummy2[5];
  /* 0x20 */
  volatile uint16_t intctrl;
  volatile uint16_t dummy3[7];
  /* 0x30 */
  volatile uint16_t asidata;
  union {
    volatile uint16_t ctrl;
    volatile uint16_t stat;
  } asi;
  volatile uint16_t asiclk;
  volatile uint16_t jpit1_ro[2];
  volatile uint16_t jpit2_ro[2];
  volatile uint16_t dummy4;
  /* 0x40 */
};

#define JERRYREGS ((struct jerry_registers *)0xf10000)

#endif
