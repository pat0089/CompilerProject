	.text
.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	push	%eax
	movl	$0, %eax
	push	%eax
_lab0:
	movl	-8(%ebp), %eax
	push	%eax
	movl	$10, %eax
	pop		%ecx
	cmpl	%eax, %ecx
	movl	$0, %eax
	setl	%al
	cmpl	$0, %eax
	je		_lab1
	movl	-8(%ebp), %eax
	push	%eax
	movl	$1, %eax
	pop		%ecx
	addl	%ecx, %eax
	movl	%eax, -8(%ebp)
	movl	$2, %eax
	push	%eax
	movl	-8(%ebp), %eax
	pop		%ecx
	cdq
	idivl	%ecx
	cmpl	$0, %eax
	je		_lab3
	jmp		_lab2
_lab3:
	movl	-4(%ebp), %eax
	push	%eax
	movl	-8(%ebp), %eax
	pop		%ecx
	addl	%ecx, %eax
	movl	%eax, -4(%ebp)
_lab2:
	jmp		_lab0
_lab1:
	addl	$4, %esp
	movl	-4(%ebp), %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
