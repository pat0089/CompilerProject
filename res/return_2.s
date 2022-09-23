.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$2, %eax
	push	%eax
	movl	$4, %eax
	pop		%ecx
	cdq
	idivl	%ecx
	movl	%edx, %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
