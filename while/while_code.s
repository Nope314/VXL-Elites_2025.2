	.cpu arm7tdmi
	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"while_code.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%d \000"
	.align	2
.LC1:
	.ascii	"%d \012\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	mov	r3, #0
	str	r3, [fp, #-8]
	mov	r3, #100
	str	r3, [fp, #-20]
	mov	r3, #0
	str	r3, [fp, #-12]
	mvn	r3, #0
	str	r3, [fp, #-24]
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L2
.L3:
	ldr	r1, [fp, #-8]
	ldr	r0, .L8
	bl	printf
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L2:
	ldr	r3, [fp, #-8]
	cmp	r3, #4
	ble	.L3
	mov	r0, #10
	bl	putchar
	nop
	b	.L4
.L5:
	ldr	r1, [fp, #-20]
	ldr	r0, .L8+4
	bl	printf
.L4:
	ldr	r3, [fp, #-20]
	cmp	r3, #0
	bne	.L5
.L6:
	ldr	r1, [fp, #-12]
	ldr	r0, .L8
	bl	printf
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-12]
	cmp	r3, #4
	ble	.L6
	mov	r0, #10
	bl	putchar
	ldr	r1, [fp, #-24]
	ldr	r0, .L8
	bl	printf
	mov	r0, #10
	bl	putchar
.L7:
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
	b	.L7
.L9:
	.align	2
.L8:
	.word	.LC0
	.word	.LC1
	.size	main, .-main
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
