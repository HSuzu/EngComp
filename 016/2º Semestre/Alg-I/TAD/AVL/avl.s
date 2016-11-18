	.file	"avl.c"
	.text
	.globl	cria
	.type	cria, @function
cria:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	cria, .-cria
	.globl	delete
	.type	delete, @function
delete:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L3
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	delete
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	delete
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free
.L2:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	delete, .-delete
	.globl	rEE
	.type	rEE, @function
rEE:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-16(%rbp), %rax
	movl	$0, 16(%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	rEE, .-rEE
	.globl	rDD
	.type	rDD, @function
rDD:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-16(%rbp), %rax
	movl	$0, 16(%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	rDD, .-rDD
	.section	.rodata
.LC0:
	.string	"-1\n"
	.text
	.globl	rED
	.type	rED, @function
rED:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movl	16(%rax), %eax
	testl	%eax, %eax
	je	.L9
	cmpl	$1, %eax
	je	.L10
	cmpl	$-1, %eax
	jne	.L13
	movq	-8(%rbp), %rax
	movl	$1, 16(%rax)
	movq	-16(%rbp), %rax
	movl	$0, 16(%rax)
	jmp	.L12
.L9:
	movq	-8(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-16(%rbp), %rax
	movl	$0, 16(%rax)
	jmp	.L12
.L10:
	movq	-8(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-16(%rbp), %rax
	movl	$-1, 16(%rax)
	jmp	.L12
.L13:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movl	$.LC0, %edi
	call	fwrite
	nop
.L12:
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movl	$0, 16(%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	rED, .-rED
	.globl	rDE
	.type	rDE, @function
rDE:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	movl	16(%rax), %eax
	testl	%eax, %eax
	je	.L16
	cmpl	$1, %eax
	je	.L17
	cmpl	$-1, %eax
	jne	.L20
	movq	-8(%rbp), %rax
	movl	$1, 16(%rax)
	movq	-16(%rbp), %rax
	movl	$0, 16(%rax)
	jmp	.L19
.L16:
	movq	-8(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-16(%rbp), %rax
	movl	$0, 16(%rax)
	jmp	.L19
.L17:
	movq	-8(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-16(%rbp), %rax
	movl	$-1, 16(%rax)
	jmp	.L19
.L20:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movl	$.LC0, %edi
	call	fwrite
	nop
.L19:
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movl	$0, 16(%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	rDE, .-rDE
	.globl	r_inserir
	.type	r_inserir, @function
r_inserir:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L22
	movl	$24, %edi
	call	malloc
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L23
	movl	$-1, %eax
	jmp	.L24
.L23:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, 8(%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$0, 16(%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	-32(%rbp), %rdx
	movl	(%rdx), %edx
	movl	%edx, 20(%rax)
	movq	-40(%rbp), %rax
	movl	$1, (%rax)
	movl	$0, %eax
	jmp	.L24
.L22:
	movq	-32(%rbp), %rax
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	20(%rax), %eax
	cmpl	%eax, %edx
	jne	.L25
	movl	$1, %eax
	jmp	.L24
.L25:
	movl	$0, -4(%rbp)
	movq	-32(%rbp), %rax
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	20(%rax), %eax
	cmpl	%eax, %edx
	jle	.L26
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	r_inserir
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L33
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L33
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	16(%rax), %eax
	testl	%eax, %eax
	je	.L28
	cmpl	$1, %eax
	je	.L29
	cmpl	$-1, %eax
	je	.L30
	jmp	.L33
.L30:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$0, 16(%rax)
	movq	-40(%rbp), %rax
	movl	$0, (%rax)
	jmp	.L27
.L28:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$1, 16(%rax)
	movq	-40(%rbp), %rax
	movl	$1, (%rax)
	jmp	.L27
.L29:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movl	16(%rax), %eax
	cmpl	$1, %eax
	jne	.L31
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	rDD
	jmp	.L32
.L31:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	rDE
.L32:
	movq	-40(%rbp), %rax
	movl	$0, (%rax)
	nop
.L27:
	jmp	.L33
.L26:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	8(%rax), %rcx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	r_inserir
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L33
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L33
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	16(%rax), %eax
	testl	%eax, %eax
	je	.L34
	cmpl	$1, %eax
	je	.L35
	cmpl	$-1, %eax
	jne	.L33
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	movl	16(%rax), %eax
	cmpl	$-1, %eax
	jne	.L37
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	rEE
	jmp	.L38
.L37:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	rED
.L38:
	movq	-40(%rbp), %rax
	movl	$0, (%rax)
	jmp	.L33
.L34:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$-1, 16(%rax)
	movq	-40(%rbp), %rax
	movl	$1, (%rax)
	jmp	.L33
.L35:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$0, 16(%rax)
	movq	-40(%rbp), %rax
	movl	$0, (%rax)
	nop
.L33:
	movl	-4(%rbp), %eax
.L24:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	r_inserir, .-r_inserir
	.globl	inserir
	.type	inserir, @function
inserir:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	leaq	-4(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	r_inserir
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	inserir, .-inserir
	.globl	r_pai
	.type	r_pai, @function
r_pai:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L42
	movl	$-1, %eax
	jmp	.L43
.L42:
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	movl	20(%rax), %eax
	cmpl	%eax, %edx
	jle	.L44
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movl	20(%rax), %eax
	cmpl	%eax, %edx
	jne	.L45
	movq	-8(%rbp), %rax
	movl	20(%rax), %eax
	jmp	.L43
.L45:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	r_pai
	jmp	.L43
.L44:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	jne	.L46
	movl	$-1, %eax
	jmp	.L43
.L46:
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movl	20(%rax), %eax
	cmpl	%eax, %edx
	jne	.L47
	movq	-8(%rbp), %rax
	movl	20(%rax), %eax
	jmp	.L43
.L47:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	r_pai
.L43:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	r_pai, .-r_pai
	.globl	pai
	.type	pai, @function
pai:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movl	20(%rax), %edx
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L49
	movl	$-1, %eax
	jmp	.L50
.L49:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	r_pai
.L50:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	pai, .-pai
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
