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

	.globl	_bzero
	.globl	_memset
		
;;; void bzero(void *b, size_t n)	
_bzero:
	move.l	4(sp),a0
	moveq	#0,d0
	move.l	8(sp),a1
	bra.s	__memset
;;; void *memset (void *s, int c, size_t n)
_memset:
	move.l	4(sp),a0
	move.b	11(sp),d0
	move.b	d0,d1
	lsl.w	#8,d0
	move.b	d1,d0
	move.w	d0,d1
	swap	d0
	move.w	d1,d0
	move.l	12(sp),a1
__memset:
;;; a0 = s, d0 = fill, a1 = n
	move.w	d2,-(sp)	
	move.l	a1,d1
	beq.s	.memset_end
	move.w	a0,d2
	lsr.w	#1,d2
	bcc.s	.src_pad2
	move.b	d0,(a0)+
	subq.l	#1,d1
	beq.s	.memset_end
.src_pad2:
	move.w	d1,d2
	lsr.l	#2,d1		; /4
	beq.s	.last_bytes
.fill_pattern:
	move.l	d0,(a0)+
	subq.l	#1,d1
	bne.s	.fill_pattern
.last_bytes:
	and.w	#%11,d2
	beq.s	.memset_end
	subq.w	#1,d2
.fill_last:
	move.b	d0,(a0)+
	dbf	d2,.fill_last
.memset_end:
	move.w	(sp)+,d2
	move.l	4(sp),d0
	rts
