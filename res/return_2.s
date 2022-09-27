.globl main
main:
	push	%ebp
	movl	%esp, %ebp
	movl	$72, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$101, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$108, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$108, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$111, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$44, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$32, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$87, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$111, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$114, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$108, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$100, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$33, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$10, %eax
	push	%eax
	call	putchar
	addl	$4, %esp
	movl	$0, %eax
	movl	%ebp, %esp
	pop		%ebp
	ret
