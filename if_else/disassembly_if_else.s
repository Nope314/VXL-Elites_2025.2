
if_else.o:     file format elf32-littlearm
if_else.o
architecture: armv4t, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x00000000
private flags = 0x5000000: [Version5 EABI]

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0000005c  00000000  00000000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  00000000  00000000  00000090  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  00000000  00000000  00000090  2**0
                  ALLOC
  3 .rodata       0000002c  00000000  00000000  00000090  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .comment      00000044  00000000  00000000  000000bc  2**0
                  CONTENTS, READONLY
  5 .ARM.attributes 0000002a  00000000  00000000  00000100  2**0
                  CONTENTS, READONLY
SYMBOL TABLE:
00000000 l    df *ABS*	00000000 if_else.c
00000000 l    d  .text	00000000 .text
00000000 l    d  .data	00000000 .data
00000000 l    d  .bss	00000000 .bss
00000000 l    d  .rodata	00000000 .rodata
00000000 l    d  .comment	00000000 .comment
00000000 l    d  .ARM.attributes	00000000 .ARM.attributes
00000000 g     F .text	0000005c main
00000000         *UND*	00000000 puts



Disassembly of section .text:

00000000 <main>:
   0:	e92d4800 	push	{fp, lr}
   4:	e28db004 	add	fp, sp, #4
   8:	e24dd008 	sub	sp, sp, #8
   c:	e3a03005 	mov	r3, #5
  10:	e50b3008 	str	r3, [fp, #-8]
  14:	e3a0300a 	mov	r3, #10
  18:	e50b300c 	str	r3, [fp, #-12]
  1c:	e51b2008 	ldr	r2, [fp, #-8]
  20:	e51b300c 	ldr	r3, [fp, #-12]
  24:	e1520003 	cmp	r2, r3
  28:	da000002 	ble	38 <main+0x38>
  2c:	e59f0020 	ldr	r0, [pc, #32]	@ 54 <main+0x54>
  30:	ebfffffe 	bl	0 <puts>
			30: R_ARM_CALL	puts
  34:	ea000001 	b	40 <main+0x40>
  38:	e59f0018 	ldr	r0, [pc, #24]	@ 58 <main+0x58>
  3c:	ebfffffe 	bl	0 <puts>
			3c: R_ARM_CALL	puts
  40:	e3a03000 	mov	r3, #0
  44:	e1a00003 	mov	r0, r3
  48:	e24bd004 	sub	sp, fp, #4
  4c:	e8bd4800 	pop	{fp, lr}
  50:	e12fff1e 	bx	lr
			50: R_ARM_V4BX	*ABS*
  54:	00000000 	andeq	r0, r0, r0
			54: R_ARM_ABS32	.rodata
  58:	00000014 	andeq	r0, r0, r4, lsl r0
			58: R_ARM_ABS32	.rodata

Disassembly of section .rodata:

00000000 <.rodata>:
   0:	73692061 	cmnvc	r9, #97	@ 0x61
   4:	65726720 	ldrbvs	r6, [r2, #-1824]!	@ 0xfffff8e0
   8:	72657461 	rsbvc	r7, r5, #1627389952	@ 0x61000000
   c:	61687420 	cmnvs	r8, r0, lsr #8
  10:	0062206e 	rsbeq	r2, r2, lr, rrx
  14:	73692061 	cmnvc	r9, #97	@ 0x61
  18:	746f6e20 	strbtvc	r6, [pc], #-3616	@ 20 <.rodata+0x20>
  1c:	65726720 	ldrbvs	r6, [r2, #-1824]!	@ 0xfffff8e0
  20:	72657461 	rsbvc	r7, r5, #1627389952	@ 0x61000000
  24:	61687420 	cmnvs	r8, r0, lsr #8
  28:	0062206e 	rsbeq	r2, r2, lr, rrx

Disassembly of section .comment:

00000000 <.comment>:
   0:	43434700 	movtmi	r4, #14080	@ 0x3700
   4:	4728203a 			@ <UNDEFINED> instruction: 0x4728203a
   8:	5420554e 	strtpl	r5, [r0], #-1358	@ 0xfffffab2
   c:	736c6f6f 	cmnvc	ip, #444	@ 0x1bc
  10:	726f6620 	rsbvc	r6, pc, #32, 12	@ 0x2000000
  14:	4d545320 	ldclmi	3, cr5, [r4, #-128]	@ 0xffffff80
  18:	31203233 			@ <UNDEFINED> instruction: 0x31203233
  1c:	2e332e33 	mrccs	14, 1, r2, cr3, cr3, {1}
  20:	316c6572 	smccc	50770	@ 0xc652
  24:	3230322e 	eorscc	r3, r0, #-536870910	@ 0xe0000002
  28:	32353035 	eorscc	r3, r5, #53	@ 0x35
  2c:	39302d33 	ldmdbcc	r0!, {r0, r1, r4, r5, r8, sl, fp, sp}
  30:	20293030 	eorcs	r3, r9, r0, lsr r0
  34:	332e3331 			@ <UNDEFINED> instruction: 0x332e3331
  38:	3220312e 	eorcc	r3, r0, #-2147483637	@ 0x8000000b
  3c:	30343230 	eorscc	r3, r4, r0, lsr r2
  40:	00343136 	eorseq	r3, r4, r6, lsr r1

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002941 	andeq	r2, r0, r1, asr #18
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	0000001f 	andeq	r0, r0, pc, lsl r0
  10:	00543405 	subseq	r3, r4, r5, lsl #8
  14:	01080206 	tsteq	r8, r6, lsl #4
  18:	04120109 	ldreq	r0, [r2], #-265	@ 0xfffffef7
  1c:	01150114 	tsteq	r5, r4, lsl r1
  20:	01180317 	tsteq	r8, r7, lsl r3
  24:	011a0119 	tsteq	sl, r9, lsl r1
  28:	Address 0x28 is out of bounds.

