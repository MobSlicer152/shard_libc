.section .text

.global _start
_start:
	# Put main's arguments in the right places
	popq %rdi # argc
	movq %rsp, %rsi # argv

	# Set up the end of the stack frame list
	xorq %rbp, %rbp
	pushq %rbp
	pushq %rbp
	movq %rsp, %rbp

	# Call C library initialization
	call __init_libc

	# Call global constructors
	call _init

	# Call the function that sets up some other stuff then calls main
	call __libc_call_main

	# Call destructors
	call _fini

	# Exit
	movl %eax, %edi
	call exit

	# Already said this in the exit file, but
	# exit returning means something is really wrong
	hlt

.size _start, . - _start
