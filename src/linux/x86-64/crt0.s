.section .text

.global _start
_start:
	xorq %rbp, %rbp
	pushq %rbp # rip=0
	pushq %rbp # rbp=0
	movq %rsp, %rbp

	# Put main's arguments in the right places
	popq %rdi # argc
	movq %rsp, %rsi # argv

	# Set up the end of the stack frame list
	xorq %rbp, %rbp
	pushq %rbp
	pushq %rbp
	movq %rsp, %rbp

	# Call C library initialization
	callq __init_libc

	# Call the function that sets up some other stuff then calls main
	callq __libc_call_main

.size _start, . - _start
