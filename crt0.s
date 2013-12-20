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

	include	"jaguar.inc"

	.text
	.68000

	.extern	_main
	.extern	_bzero
	.globl	_text_start
	.globl	_reset
	.extern	_BSS_E

_reset:
_text_start:
        move.w  #$100,JOYSTICK	; mute sound
        move.l  #0,G_CTRL	; stop GPU
        move.l  #0,D_CTRL	; stop DSP
        move.l  #0,G_FLAGS	; init GPU flags
        move.l  #0,D_FLAGS	; init DSP flags
        move.l  #$00070007,G_END	; GPU in BigEndian
        move.l  #$00070007,D_END	; DSP in BigEndian
        move.w  #%11010111001100,MEMCON2	; memory in BigEndian
        move.w  #$ffff,VI	; disable video interrupts
	;; wait blitter
.wait_blitter:
	move.l	B_CMD,d0
	btst.l	#0,d0
	beq.s	.wait_blitter
	move.l	#0,A1_CLIP	; A1_CLIP workaround
	;;
	move.l	#INITSTACK,sp	; init SP
	;; clear BSS section
	move.l	#_BSS_E,d0
	sub.l	#_bss_start,d0
	move.l	d0,-(sp)
	move.l	#_bss_start,-(sp)
	jsr	_bzero
	addq.w	#8,sp
	;; init video
	bsr	init_video
	;; empty object list
	move.l	#_stop_object,d0
	swap	d0
	move.l	d0,OLP
	;; jump to main
	jmp	_main

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Procedure: Interlace
;            Sets up video signals correctly to enable interlaced video
;            Modifies registers we were told never to touch.
;            Code by Zerosquare of Jagware
;
        .globl  _Interlace
_Interlace:
	move.w	CONFIG, d0
	andi.w	#16, d0
	bne.s	.Init60HzI
.Init50HzI:
	move.w	#0,	HC
	move.w	#1,	VC
	move.w	#624,	VP
	move.w	#614,	VEB
	move.w	#619,	VS
	move.w	#4,	VEE
	move.w	#40,	VBE
	move.w	#614,	VBB
	move.w	#850,	HP
	move.w	#1749,	HS
	move.w	#787,	HEQ
	move.w	#600,	HVS
	move.w	#1709,	HBB
	move.w	#153,	HBE
	bra.s	done
.Init60HzI:
	move.w	#0,	HC
	move.w	#1,	VC
	move.w	#524,	VP
	move.w	#512,	VEB
	move.w	#518,	VS
	move.w	#5,	VEE
	move.w	#30,	VBE
	move.w	#512,	VBB
	move.w	#844,	HP
	move.w	#1743,	HS
	move.w	#780,	HEQ
	move.w	#595,	HVS
	move.w	#1697,	HBB
	move.w	#118,	HBE
.done:
	rts

        .globl  _InitVideo
_InitVideo:
	movem.l	d2-d6,-(sp)
	move.w	CONFIG,d0	; Also is joystick register
	andi.w	#VIDTYPE,d0	;0=PAL,1=NTSC
	beq	.palvals
	move.w	#60,_vblPerSec	; 60 Hz
	move.w	#NTSC_HMID,d2
	move.w	#NTSC_WIDTH,d0
	move.w	#NTSC_VMID,d6
	move.w	#NTSC_HEIGHT,d4
	bra	.calc_vals
.palvals:
	move.w	#50,_vblPerSec	; 50 Hz
	move.w	#PAL_HMID,d2
	move.w	#PAL_WIDTH,d0
	move.w	#PAL_VMID,d6
	move.w	#PAL_HEIGHT,d4
.calc_vals:
	move.w	d0,_video_width
	move.w	d4,_video_height
	move.w	d0,d1
	asr.w	#1,d1		;Width/2
	sub.w	d1,d2		;Mid-Width/2
	add.w	#4,d2		;(Mid-Width/2)+4
	sub.w	#1,d1		;Width/2-1
	ori.w	#$400,d1	;(Width/2-1)|$400
	move.w	d1,_a_hde
	move.w	d1,HDE
	move.w	d2,_a_hdb
	move.w	d2,HDB1
	move.w	d2,HDB2
	move.w	d6,d5
	sub.w	d4,d5
	move.w	d5,_a_vdb
	add.w	d4,d6
	move.w	d6,_a_vde
	move.w	_a_vdb,VDB
*	move.w	#$FFFF,VDE
	move.w	_a_vde,VDE
	move.l	#0,BORD1	;Blackborder
	move.l	#0,BG
	movem.l	(sp)+,d2-d6
	rts

	.data

	.globl	_data_start
	.globl	_stop_object

	.qphrase
_data_start:

	.phrase
_stop_object:
	dc.l	0,STOPOBJ

	.bss
	.qphrase
_bss_start:

	.globl	_video_height
	.globl	_a_vdb
	.globl	_a_vde
	.globl	_video_width
	.globl	_a_hdb
	.globl	_a_hde

	.globl	_vblPerSec

	.even
_video_height:	ds.w    1
_a_vdb:		ds.w    1
_a_vde:		ds.w    1
_video_width:	ds.w    1
_a_hdb:		ds.w    1
_a_hde:		ds.w    1
_vblPerSec:	ds.w	1



