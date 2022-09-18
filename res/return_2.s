.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$1, %eax
	push	%eax
	movl	$0, %eax
	push	%eax
	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	movl	$0, %eax
	sete	%al
	cmpl	$0, %eax
	je		_lab0
	movl	-8(%ebp), %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
_lab0:
	movl	-8(%ebp), %eax
	cmpl	$0, %eax
	je		_lab1
	movl	-4(%ebp), %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
_lab1:
	movl	$0, %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
