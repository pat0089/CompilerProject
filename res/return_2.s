.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	push	%eax
	movl	$1, %eax
	pop		%ecx
	and		%ecx, %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
