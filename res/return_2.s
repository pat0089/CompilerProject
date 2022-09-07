.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	push	%eax
	movl	$5, %eax
	push	%eax
	movl	$3, %eax
	movl	%eax, -4(%ebp)
	movl	-8(%ebp), %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
