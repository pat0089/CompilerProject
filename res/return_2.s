	.text
.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	%ebp, %esp
	pop		%ebp
	ret
