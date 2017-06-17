	.file	"figura1-modificado_ab.c"
	.section	.rodata
.LC1:
	.string	"\nR[%d] = %d"
.LC2:
	.string	"\n\ntiempo: %f"
.LC3:
	.string	"a"
.LC4:
	.string	"figura1_salida"
.LC5:
	.string	"Error opening file."
.LC6:
	.string	"\nmodificadoAB\t%f"
	.text
	.globl	main
	.type	main, @function
main:
.LFB499:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$240080, %rsp
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	cltq
	movl	-4(%rbp), %edx
	movl	%edx, -40064(%rbp,%rax,8)
	movl	$4999, %eax
	subl	-4(%rbp), %eax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	cltq
	movl	%edx, -40060(%rbp,%rax,8)
	addl	$1, -4(%rbp)
.L2:
	cmpl	$4999, -4(%rbp)
	jle	.L3
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime
	movl	$0, -4(%rbp)
	jmp	.L4
.L5:
	movl	-4(%rbp), %eax
	cltq
	movl	$0, -80064(%rbp,%rax,8)
	movl	-4(%rbp), %eax
	cltq
	movl	$0, -80060(%rbp,%rax,8)
	movl	-4(%rbp), %eax
	cltq
	movl	-40064(%rbp,%rax,8), %edx
	movl	-4(%rbp), %eax
	cltq
	movl	-40064(%rbp,%rax,8), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	cltq
	movl	%edx, -80064(%rbp,%rax,8)
	movl	-4(%rbp), %eax
	cltq
	movl	-40060(%rbp,%rax,8), %edx
	movl	-4(%rbp), %eax
	cltq
	movl	-40060(%rbp,%rax,8), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	cltq
	movl	-40060(%rbp,%rax,8), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	cltq
	movl	%edx, -80060(%rbp,%rax,8)
	addl	$1, -4(%rbp)
.L4:
	cmpl	$4999, -4(%rbp)
	jle	.L5
	movl	$0, -8(%rbp)
	jmp	.L6
.L11:
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L7
.L8:
	movl	-4(%rbp), %eax
	cltq
	movl	-80064(%rbp,%rax,8), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	addl	%eax, -12(%rbp)
	movl	-4(%rbp), %eax
	cltq
	movl	-80060(%rbp,%rax,8), %eax
	subl	-8(%rbp), %eax
	addl	%eax, -16(%rbp)
	addl	$1, -4(%rbp)
.L7:
	cmpl	$4999, -4(%rbp)
	jle	.L8
	movl	-12(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jge	.L9
	movl	-8(%rbp), %eax
	cltq
	movl	-12(%rbp), %edx
	movl	%edx, -240064(%rbp,%rax,4)
	jmp	.L10
.L9:
	movl	-8(%rbp), %eax
	cltq
	movl	-16(%rbp), %edx
	movl	%edx, -240064(%rbp,%rax,4)
.L10:
	addl	$1, -8(%rbp)
.L6:
	cmpl	$39999, -8(%rbp)
	jle	.L11
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime
	movq	-64(%rbp), %rdx
	movq	-48(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm1
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC0(%rip), %xmm2
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L12
.L13:
	movl	-4(%rbp), %eax
	cltq
	movl	-240064(%rbp,%rax,4), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addl	$12345, -4(%rbp)
.L12:
	cmpl	$39999, -4(%rbp)
	jle	.L13
	movq	-24(%rbp), %rax
	movq	%rax, -240072(%rbp)
	movsd	-240072(%rbp), %xmm0
	movl	$.LC2, %edi
	movl	$1, %eax
	call	printf
	movl	$.LC3, %esi
	movl	$.LC4, %edi
	call	fopen
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L14
	movl	$.LC5, %edi
	call	perror
.L14:
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, -240072(%rbp)
	movsd	-240072(%rbp), %xmm0
	movl	$.LC6, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fclose
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE499:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1104006501
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
