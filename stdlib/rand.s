; Jaguar C library
; Copyright (C) 2006 Seb/The Removers
; http://removers.atari.org/
	
; This library is free software; you can redistribute it and/or
; modify it under the terms of the GNU Lesser General Public
; License as published by the Free Software Foundation; either
; version 2.1 of the License, or (at your option) any later version.

; This library is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
; Lesser General Public License for more details.

; You should have received a copy of the GNU Lesser General Public
; License along with this library; if not, write to the Free Software
; Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

	.text
	.68000

RANDGEN_J	equ	3
RANDGEN_MOD	equ	3
RANDGEN_K	equ	(1<<RANDGEN_MOD)-1	; k > j (doit etre le predecesseur d'une puissance de 2)
RANDGEN_R	equ	5
	
	.globl	_srand
_srand:	
	move.l	d2,-(sp)
	move.l	#random_seeds,a0
	move.l	4(sp),d1
	move.l	d1,d2
	moveq	#RANDGEN_K,d0
.init_seeds:
	eor.l	#$31415926,d1
	move.l	d1,(a0)+
	ror.l	#8,d1
	ror.l	#5,d1
	add.l	d2,d1
	dbf	d0,.init_seeds
	move.w	#RANDGEN_K*4,random_index
	move.l	(sp)+,d2
	rts
	
	.globl	_rand
; _rand:
; 	move.l	d2,-(sp)
; 	move.w	random_index,d1
; 	move.w	d1,d2
; 	sub.w	#(RANDGEN_J-RANDGEN_K)*4,d2
; 	and.w	#RANDGEN_K<<2,d2
; 	move.l	#random_seeds,a0
; 	move.l	(a0,d1.w),d0
; 	add.l	(a0,d2.w),d0
; 	ror.l	#RANDGEN_R,d0
; 	move.l	d0,(a0,d1.w)
; 	subq.w	#4,d1
; 	and.w	#RANDGEN_K<<2,d1
; 	move.w	d1,random_index
; 	move.l	(sp)+,d2
; 	rts
_rand:
	move.w	random_index,d0
	move.w	d0,d1
	sub.w	#(RANDGEN_J-RANDGEN_K)*4,d0
	and.w	#RANDGEN_K<<2,d0
	move.l	#random_seeds,a0
	move.l	(a0,d0.w),d0
	add.l	(a0,d1.w),d0
	ror.l	#RANDGEN_R,d0
	move.l	d0,(a0,d1.w)
	subq.w	#4,d1
	and.w	#RANDGEN_K<<2,d1
	move.w	d1,random_index
	rts

	.bss
	.long
random_index:
	ds.w	1
	ds.w	1
random_seeds:
	ds.l	RANDGEN_K+1

