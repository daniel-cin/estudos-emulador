	.cpu cortex-m3
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"test_program.c"
	.text
	.section	.rodata
	.align	2
	.type	a, %object
	.size	a, 4
a:
	.word	7
	.data
	.align	2
	.type	b, %object
	.size	b, 4
b:
	.word	8
	.bss
	.align	2
sum:
	.space	4
	.size	sum, 4
	.text
	.align	1
	.global	main
	.arch armv7-m
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	movs	r2, #7
	ldr	r3, .L2
	ldr	r3, [r3]
	add	r3, r3, r2
	ldr	r2, .L2+4
	str	r3, [r2]
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L3:
	.align	2
.L2:
	.word	b
	.word	sum
	.size	main, .-main
	.ident	"GCC: (15:10.3-2021.07-4) 10.3.1 20210621 (release)"
