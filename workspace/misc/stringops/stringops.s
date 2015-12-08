	.file	"stringops.c"
	.text
	.globl	ReverseString
	.type	ReverseString, @function
ReverseString:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L2
	jmp	.L1
.L2:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movl	%eax, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L4
.L5:
	movl	-8(%rbp), %edx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -9(%rbp)
	movl	-8(%rbp), %edx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-8(%rbp), %eax
	movl	-4(%rbp), %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	subl	$1, %eax
	movl	%eax, %ecx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	movl	-8(%rbp), %eax
	movl	-4(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	subl	$1, %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-9(%rbp), %eax
	movb	%al, (%rdx)
	addl	$1, -8(%rbp)
.L4:
	movl	-4(%rbp), %eax
	shrl	%eax
	cmpl	-8(%rbp), %eax
	ja	.L5
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	ReverseString, .-ReverseString
	.globl	RecursiveReverseString
	.type	RecursiveReverseString, @function
RecursiveReverseString:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	cmpl	$0, -28(%rbp)
	jle	.L6
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -1(%rbp)
	movl	-28(%rbp), %eax
	cltq
	leaq	-1(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movq	-24(%rbp), %rax
	movb	%dl, (%rax)
	movl	-28(%rbp), %eax
	cltq
	leaq	-1(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-1(%rbp), %eax
	movb	%al, (%rdx)
	movl	-28(%rbp), %eax
	leal	-2(%rax), %edx
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	RecursiveReverseString
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	RecursiveReverseString, .-RecursiveReverseString
	.globl	StrStr
	.type	StrStr, @function
StrStr:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L9
	cmpq	$0, -48(%rbp)
	jne	.L10
.L9:
	movl	$0, %eax
	jmp	.L11
.L10:
	movq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	jmp	.L12
.L14:
	addq	$1, -24(%rbp)
.L12:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	je	.L13
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L14
.L13:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L15
	movl	$0, %eax
	jmp	.L11
.L15:
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L16
.L18:
	addq	$1, -24(%rbp)
	addq	$1, -16(%rbp)
.L16:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	jne	.L17
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L17
	cmpq	$0, -16(%rbp)
	jne	.L18
.L17:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L19
	movq	-8(%rbp), %rax
	jmp	.L11
.L19:
	movl	$0, %eax
.L11:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	StrStr, .-StrStr
	.globl	CountAllOnes1
	.type	CountAllOnes1, @function
CountAllOnes1:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L21
.L22:
	movq	-24(%rbp), %rax
	andl	$1, %eax
	addl	%eax, -4(%rbp)
	shrq	-24(%rbp)
.L21:
	cmpq	$0, -24(%rbp)
	jne	.L22
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	CountAllOnes1, .-CountAllOnes1
	.data
	.align 32
	.type	BitMap16, @object
	.size	BitMap16, 64
BitMap16:
	.long	0
	.long	1
	.long	1
	.long	2
	.long	1
	.long	2
	.long	2
	.long	3
	.long	1
	.long	2
	.long	2
	.long	3
	.long	2
	.long	3
	.long	3
	.long	4
	.text
	.globl	CountAllOnes2
	.type	CountAllOnes2, @function
CountAllOnes2:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	andl	$15, %eax
	movl	BitMap16(,%rax,4), %edx
	movq	-24(%rbp), %rax
	shrq	$4, %rax
	andl	$15, %eax
	movl	BitMap16(,%rax,4), %eax
	addl	%eax, %edx
	movq	-24(%rbp), %rax
	shrq	$8, %rax
	andl	$15, %eax
	movl	BitMap16(,%rax,4), %eax
	addl	%eax, %edx
	movq	-24(%rbp), %rax
	shrq	$12, %rax
	andl	$15, %eax
	movl	BitMap16(,%rax,4), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	CountAllOnes2, .-CountAllOnes2
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
