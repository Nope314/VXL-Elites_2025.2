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
	.file	"if_else.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"a is greater than b\000"
	.align	2
.LC1:
	.ascii	"a is not greater than b\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr} //fp là con trỏ khung , giúp truy cập biến local và tham số
	add	fp, sp, #4 //đặt giá trị của fp bằng giá trị của sp cộng với 4
	sub	sp, sp, #8 //giảm stack pointer để tạo không gian cho frame
	mov	r3, #5
	str	r3, [fp, #-8] //lưu giá trị 5 vào ô nhớ tại fp-8
	mov	r3, #10
	str	r3, [fp, #-12] 
	ldr	r2, [fp, #-8] 
	ldr	r3, [fp, #-12]
	cmp	r2, r3 //if_else
	ble	.L2
	ldr	r0, .L5
	bl	puts
	b	.L3
.L2:
	ldr	r0, .L5+4
	bl	puts //đây là printf nhưng chỉ có 1 tham số là chuỗi nên nó sẽ gọi puts
.L3:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4 //khôi phục lại stack pointer
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L6:
	.align	2
.L5:
	.word	.LC0
	.word	.LC1
	.size	main, .-main
	.ident	"GCC: (GNU Tools for STM32 13.3.rel1.20250523-0900) 13.3.1 20240614"
