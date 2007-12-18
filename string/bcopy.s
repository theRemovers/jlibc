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

        .globl  _memcpy
        .globl  _memmove
        .globl  _bcopy

;;; void *memcpy(void *dest, const void *src, size_t n)
;;; void *memmove(void *dest, const void *src, size_t n)
_memcpy:
_memmove:
        move.l  4(sp),a1        ; dst
        move.l  8(sp),a0        ; src
        move.l  12(sp),d0       ; n
        bra.s   __memmove
;;; void bcopy(const void *src, void *dst, size_t n)
_bcopy:
        move.l  8(sp),a1        ; dst
        move.l  4(sp),a0        ; src
        move.l  12(sp),d0       ; n
__memmove:
;;; a0 = src, a1 = dst, d0 = n
        move.l a2,-(sp)
        tst.l   d0
        beq     .done
        cmp.l   a0,a1
        beq     .done
        blo.s   .fwd_copy
.dst_hi_src:
        lea     (a0,d0.l),a2    ; end src
        cmp.l   a2,a1
        bhi.s   .fwd_copy
.bwd_copy:
        ;; backward copy (slow)
	lea	(a2),a0
	lea	(a1,d0.l),a1
	move.w	a0,d1
	lsr.w	#1,d1
	bcc.s	.bwd_src_even
.bwd_src_odd:
	move.w	a1,d1
	lsr.w	#1,d1
	bcc.s	.bwd_byte_copy
	move.b	-(a0),-(a1)
	subq.l	#1,d0
	bne.s	.bwd_long_copy
	bra.s	.done
.bwd_src_even:
	move.w	a1,d1
	lsr.w	#1,d1
	bcs.s	.bwd_byte_copy
.bwd_long_copy:
	move.l	d0,d1
	lsr.l	#2,d0
	beq.s	.bwd_long_copy_last_bytes
.bwd_do_long_copy:
	move.l	-(a0),-(a1)
	subq.l	#1,d0
	bne.s	.bwd_do_long_copy
.bwd_long_copy_last_bytes:
;;; here d0.l = 0
	and.w	#%11,d1
	beq.s	.done
	move.w	d1,d0
.bwd_byte_copy:
	move.b	-(a0),-(a1)
	subq.l	#1,d0
	bne.s	.bwd_byte_copy
        bra.s	.done
.fwd_copy:	
        ;; forward copy (fast)
	move.w	a0,d1
	lsr.w	#1,d1
	bcc.s	.fwd_src_even
.fwd_src_odd:
	move.w	a1,d1
	lsr.w	#1,d1
	bcc.s	.fwd_byte_copy
	move.b	(a0)+,(a1)+
	subq.l	#1,d0
	bne.s	.fwd_long_copy
	bra.s	.done
.fwd_src_even:
	move.w	a1,d1
	lsr.w	#1,d1
	bcs.s	.fwd_byte_copy
.fwd_long_copy:
	move.l	d0,d1
	lsr.l	#2,d0
	beq.s	.fwd_long_copy_last_bytes
.fwd_do_long_copy:
	move.l	(a0)+,(a1)+
	subq.l	#1,d0
	bne.s	.fwd_do_long_copy
.fwd_long_copy_last_bytes:
;;; here, d0.l = 0
	and.w	#%11,d1
	beq.s	.done
	move.w	d1,d0
.fwd_byte_copy:
;;; src and dst have opposite parity
	move.b	(a0)+,(a1)+
	subq.l	#1,d0
	bne.s	.fwd_byte_copy
.done:	
	move.l	(sp)+,a2
	move.l	4(sp),d0
	rts
