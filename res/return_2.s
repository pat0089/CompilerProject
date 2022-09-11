.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	push	%eax
	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	je		_lab1
	movl	$1, %eax
	movl	%eax, -4(%ebp)
	jmp		_lab0
_lab1:
	movl	$2, %eax
	movl	%eax, -4(%ebp)
_lab0:
	movl	-4(%ebp), %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
