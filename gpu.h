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

/** \file gpu.h
 * \brief GPU hardware registers
 */

#ifndef __GPU_H
#define __GPU_H

#include <jagtypes.h>

struct gpu_registers {
  /* 0x00 */
  volatile uint32_t gpu_flags;
  volatile uint32_t gpu_mtxc;
  volatile uint32_t gpu_mtxa;
  volatile uint32_t gpu_bigend;
  /* 0x10 */
  volatile uint32_t gpu_pc;
  volatile uint32_t gpu_ctrl;
  volatile uint32_t gpu_hidata;
  volatile uint32_t gpu_remain;
  /* 0x20 */
  volatile uint32_t dummy1[120];
  /* 0x200 */
  volatile uint32_t blit_a1base;
  volatile uint32_t blit_a1flags;
  volatile uint32_t blit_a1win;
  volatile uint32_t blit_a1ptr;
  /* 0x210 */
  volatile uint32_t blit_a1step;
  volatile uint32_t blit_a1stepf;
  volatile uint32_t blit_a1frac;
  volatile uint32_t blit_a1inc;
  /* 0x220 */
  volatile uint32_t blit_a1incf;
  volatile uint32_t blit_a2base;
  volatile uint32_t blit_a2flags;
  volatile uint32_t blit_a2mask;
  /* 0x230 */
  volatile uint32_t blit_a2ptr;
  volatile uint32_t blit_a2step;
  volatile uint32_t blit_cmd;
  volatile uint32_t blit_count;
  /* 0x240 */
  volatile uint32_t blit_srcd[2];
  volatile uint32_t blit_dstd[2];
  /* 0x250 */
  volatile uint32_t blit_dstz[2];
  volatile uint32_t blit_srcz1[2];
  /* 0x260 */
  volatile uint32_t blit_srcz2[2];
  volatile uint32_t blit_patd[2];
  /* 0x270 */
  volatile uint32_t blit_iinc;
  volatile uint32_t blit_zinc;
  volatile uint32_t blit_stop;
  volatile uint32_t blit_i[4];
  volatile uint32_t blit_z[4];
  volatile uint32_t dummy2[857];
  volatile uint32_t gpu_ram[1024];
};

#define GPUREGS ((struct gpu_registers *)0xf02100)

#endif
