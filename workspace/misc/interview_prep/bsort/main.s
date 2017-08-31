	.file	"main.c"
	.data
	.align 16
	.type	arr, @object
	.size	arr, 20
arr:
	.long	2
	.long	5
	.long	6
	.long	7
	.long	1
	.align 4
	.type	arr_size, @object
	.size	arr_size, 4
arr_size:
	.long	5
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	arr_size(%rip), %eax
	movl	%eax, %esi
	movl	$arr, %edi
	call	sort
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.type	sort, @function
sort:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L4
.L8:
	movl	-12(%rbp), %eax
	movl	%eax, -8(%rbp)
	jmp	.L5
.L7:
	movl	-12(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jbe	.L6
	movl	-12(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-12(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rdx)
.L6:
	addl	$1, -8(%rbp)
.L5:
	movl	-8(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jb	.L7
	addl	$1, -12(%rbp)
.L4:
	movl	-12(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jb	.L8
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	sort, .-sort
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
