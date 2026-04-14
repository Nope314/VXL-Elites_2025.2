
func2.o:     file format elf32-littlearm
func2.o
architecture: armv4t, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x00000000
private flags = 0x5000000: [Version5 EABI]

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000044  00000000  00000000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  00000000  00000000  00000078  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  00000000  00000000  00000078  2**0
                  ALLOC
  3 .rodata       00000018  00000000  00000000  00000078  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .comment      00000044  00000000  00000000  00000090  2**0
                  CONTENTS, READONLY
  5 .ARM.attributes 0000002a  00000000  00000000  000000d4  2**0
                  CONTENTS, READONLY
SYMBOL TABLE:
00000000 l    df *ABS*	00000000 func2.c
00000000 l    d  .text	00000000 .text
00000000 l    d  .data	00000000 .data
00000000 l    d  .bss	00000000 .bss
00000000 l    d  .rodata	00000000 .rodata
00000000 l    d  .comment	00000000 .comment
00000000 l    d  .ARM.attributes	00000000 .ARM.attributes
00000000 g     F .text	00000024 func2
00000000         *UND*	00000000 puts
00000024 g     F .text	00000020 main



Disassembly of section .text:

00000000 <func2>:
   0:	e92d4800 	push	{fp, lr}
   4:	e28db004 	add	fp, sp, #4
   8:	e59f0010 	ldr	r0, [pc, #16]	@ 20 <func2+0x20>
   c:	ebfffffe 	bl	0 <puts>
			c: R_ARM_CALL	puts
  10:	e1a00000 	nop			@ (mov r0, r0)
  14:	e24bd004 	sub	sp, fp, #4
  18:	e8bd4800 	pop	{fp, lr}
  1c:	e12fff1e 	bx	lr
			1c: R_ARM_V4BX	*ABS*
  20:	00000000 	andeq	r0, r0, r0
			20: R_ARM_ABS32	.rodata

00000024 <main>:
  24:	e92d4800 	push	{fp, lr}
  28:	e28db004 	add	fp, sp, #4
  2c:	ebfffffe 	bl	0 <func2>
			2c: R_ARM_CALL	func2
  30:	e3a03000 	mov	r3, #0
  34:	e1a00003 	mov	r0, r3
  38:	e24bd004 	sub	sp, fp, #4
  3c:	e8bd4800 	pop	{fp, lr}
  40:	e12fff1e 	bx	lr
			40: R_ARM_V4BX	*ABS*

Disassembly of section .rodata:

00000000 <.rodata>:
   0:	73696854 	cmnvc	r9, #84, 16	@ 0x540000
   4:	20736920 	rsbscs	r6, r3, r0, lsr #18
   8:	6d6f7266 	sfmvs	f7, 2, [pc, #-408]!	@ fffffe78 <main+0xfffffe54>
   c:	68746f20 	ldmdavs	r4!, {r5, r8, r9, sl, fp, sp, lr}^
  10:	66207265 	strtvs	r7, [r0], -r5, ror #4
  14:	00656c69 	rsbeq	r6, r5, r9, ror #24

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

