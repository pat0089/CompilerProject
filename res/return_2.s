.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$2, %eax
	push	%eax
	movl	-4(%ebp), %eax
	push	%eax
	movl	$3, %eax
	pop		%ecx
	cmpl	%eax, %ecx
	movl	$0, %eax
	setl	%al
	cmpl	$0, %eax
	je		_lab0
	movl	$3, %eax
	push	%eax
	movl	-8(%ebp), %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
	addl	$4, %esp
	movl	-4(%ebp), %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
	addl	$0, %esp
_lab0:
