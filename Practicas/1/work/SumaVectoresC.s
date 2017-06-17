	.file	"SumaVectoresC.c"
	.comm	v1,268435456,32
	.comm	v2,268435456,32
	.comm	v3,268435456,32
	.section	.rodata
	.align 8
.LC0:
	.string	"Faltan n\302\272 componentes del vector"
	.align 8
.LC3:
	.string	"Tiempo(seg.):%11.9f\t / Tama\303\261o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	cmpl	$1, -52(%rbp)
	jg	.L2
	movl	$.LC0, %edi
	call	puts
	movl	$-1, %edi
	call	exit
.L2:
	movq	-64(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, -8(%rbp)
	cmpl	$33554432, -8(%rbp)
	jbe	.L3
	movl	$33554432, -8(%rbp)
.L3:
	movl	$0, -4(%rbp)
	jmp	.L4
.L9:
	movl	-8(%rbp), %eax
	testq	%rax, %rax
	js	.L5
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	jmp	.L6
.L5:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L6:
	movsd	.LC1(%rip), %xmm1
	mulsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sd	-4(%rbp), %xmm0
	movsd	.LC1(%rip), %xmm2
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movl	-4(%rbp), %eax
	cltq
	movsd	%xmm0, v1(,%rax,8)
	movl	-8(%rbp), %eax
	testq	%rax, %rax
	js	.L7
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	jmp	.L8
.L7:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L8:
	movsd	.LC1(%rip), %xmm1
	mulsd	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sd	-4(%rbp), %xmm1
	movsd	.LC1(%rip), %xmm2
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	movl	-4(%rbp), %eax
	cltq
	movsd	%xmm0, v2(,%rax,8)
	addl	$1, -4(%rbp)
.L4:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jb	.L9
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	movl	-4(%rbp), %eax
	cltq
	movsd	v1(,%rax,8), %xmm1
	movl	-4(%rbp), %eax
	cltq
	movsd	v2(,%rax,8), %xmm0
	addsd	%xmm1, %xmm0
	movl	-4(%rbp), %eax
	cltq
	movsd	%xmm0, v3(,%rax,8)
	addl	$1, -4(%rbp)
.L10:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jb	.L11
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime
	movq	-48(%rbp), %rdx
	movq	-32(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm1
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC2(%rip), %xmm2
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %eax
	movsd	v3(,%rax,8), %xmm5
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %eax
	movsd	v2(,%rax,8), %xmm4
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %eax
	movsd	v1(,%rax,8), %xmm3
	movl	-8(%rbp), %eax
	leal	-1(%rax), %edi
	movl	-8(%rbp), %eax
	leal	-1(%rax), %ecx
	movl	-8(%rbp), %eax
	leal	-1(%rax), %edx
	movsd	v3(%rip), %xmm2
	movsd	v2(%rip), %xmm1
	movsd	v1(%rip), %xmm0
	movl	-8(%rbp), %esi
	movq	-16(%rbp), %rax
	movapd	%xmm5, %xmm6
	movapd	%xmm4, %xmm5
	movapd	%xmm3, %xmm4
	movl	%edi, %r8d
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$.LC3, %edi
	movl	$7, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	2576980378
	.long	1069128089
	.align 8
.LC2:
	.long	0
	.long	1104006501
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
