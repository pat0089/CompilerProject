.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$1, %eax
	push	%eax
	movl	$2, %eax
	push	%eax
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	push	%eax
	movl	-8(%ebp), %eax
	pop		%ecx
	cmpl	%eax, %ecx
	movl	$0, %eax
	setg	%al
	cmpl	$0, %eax
	je		_lab1
	movl	-4(%ebp), %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
	jmp		_lab0
_lab1:
	movl	-8(%ebp), %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
_lab0:
