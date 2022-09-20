.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
