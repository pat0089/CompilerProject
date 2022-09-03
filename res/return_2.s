.globl main
main:
	movl	$1, %eax
	cmpl	$0, %eax
	je		_lab0
	movl	$1, %eax
	jmp		_lab1
_lab0:
	movl	$1, %eax
	neg		%eax
	cmpl	$0, %eax
	movl	$0, %eax
	setne	%al
_lab1:
	ret
