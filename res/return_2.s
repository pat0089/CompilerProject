	.text
.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	push	%eax
_lab0:
	movl	-4(%ebp), %eax
	push	%eax
	movl	$3, %eax
	pop		%ecx
	cmpl	%eax, %ecx
	movl	$0, %eax
	setl	%al
	cmpl	$0, %eax
	je		_lab1
	movl	foo, %eax
	push	%eax
	movl	$1, %eax
	pop		%ecx
	addl	%ecx, %eax
	movl	%eax, foo
_lab2:
	movl	-4(%ebp), %eax
	push	%eax
	movl	$1, %eax
	pop		%ecx
	addl	%ecx, %eax
	movl	%eax, -4(%ebp)
	jmp		_lab0
_lab1:
	addl	$4, %esp
	movl	foo, %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
.globl foo
	.bss
	.align 4
foo:
	.zero 4
