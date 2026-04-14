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
	.file	"func1.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%d \012\000"
	.text
	.align	2
	.global	foo
	.syntax unified
	.arm
	.type	foo, %function
foo:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	ldr	r1, [fp, #-8]
	ldr	r0, .L2
	bl	printf
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L3:
	.align	2
.L2:
	.word	.LC0
	.size	foo, .-foo
	.global	__aeabi_f2d
	.section	.rodata
	.align	2
.LC1:
	.ascii	"%f \012\000"
	.text
	.align	2
	.global	foo_alternative
	.syntax unified
	.arm
	.type	foo_alternative, %function
foo_alternative:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]	@ float
	ldr	r0, [fp, #-8]	@ float
	bl	__aeabi_f2d
	mov	r2, r0
	mov	r3, r1
	ldr	r0, .L5
	bl	printf
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L6:
	.align	2
.L5:
	.word	.LC1
	.size	foo_alternative, .-foo_alternative
	.section	.rodata
	.align	2
.LC2:
	.ascii	"%d\012\000"
	.text
	.align	2
	.global	foo_ptr
	.syntax unified
	.arm
	.type	foo_ptr, %function
foo_ptr:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L8
	bl	printf
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L9:
	.align	2
.L8:
	.word	.LC2
	.size	foo_ptr, .-foo_ptr
	.align	2
	.global	foo_return_int
	.syntax unified
	.arm
	.type	foo_return_int, %function
foo_return_int:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	mov	r3, #10
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	foo_return_int, .-foo_return_int
	.align	2
	.global	foo_return_local
	.syntax unified
	.arm
	.type	foo_return_local, %function
foo_return_local:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #10
	str	r3, [fp, #-8]
	mov	r3, #0
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	foo_return_local, .-foo_return_local
	.section	.rodata
	.align	2
.LC3:
	.ascii	"Test Case 1: \000"
	.align	2
.LC4:
	.ascii	"%s\000"
	.align	2
.LC5:
	.ascii	"Test Case 2: \000"
	.align	2
.LC6:
	.ascii	"Test Case 3: \000"
	.align	2
.LC7:
	.ascii	"Test Case 4: \000"
	.global	__aeabi_f2iz
	.align	2
.LC8:
	.ascii	"Test Case 5: \000"
	.global	__aeabi_i2f
	.align	2
.LC9:
	.ascii	"Test Case 6: \000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #32
	mov	r3, #1
	str	r3, [fp, #-8]
	ldr	r1, .L16
	ldr	r0, .L16+4
	bl	printf
	ldr	r0, [fp, #-8]
	bl	foo
	mov	r3, #3
	str	r3, [fp, #-32]
	sub	r3, fp, #32
	str	r3, [fp, #-12]
	ldr	r1, .L16+8
	ldr	r0, .L16+4
	bl	printf
	ldr	r0, [fp, #-12]
	bl	foo_ptr
	ldr	r1, .L16+12
	ldr	r0, .L16+4
	bl	printf
	bl	foo_return_int
	str	r0, [fp, #-16]
	ldr	r1, [fp, #-16]
	ldr	r0, .L16+16
	bl	printf
	ldr	r3, .L16+20
	str	r3, [fp, #-20]	@ float
	ldr	r1, .L16+24
	ldr	r0, .L16+4
	bl	printf
	ldr	r0, [fp, #-20]	@ float
	bl	__aeabi_f2iz
	mov	r3, r0
	mov	r0, r3
	bl	foo
	mov	r3, #1
	str	r3, [fp, #-24]
	ldr	r1, .L16+28
	ldr	r0, .L16+4
	bl	printf
	ldr	r0, [fp, #-24]
	bl	__aeabi_i2f
	mov	r3, r0
	mov	r0, r3
	bl	foo_alternative
	ldr	r1, .L16+32
	ldr	r0, .L16+4
	bl	printf
	bl	foo_return_local
	str	r0, [fp, #-28]
	ldr	r1, [fp, #-28]
	ldr	r0, .L16+16
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L17:
	.align	2
.L16:
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC0
	.word	1080033280
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.size	main, .-main
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
