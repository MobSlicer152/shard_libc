.section .text

# The syscall function's core implementation
.global __syscall
__syscall:
	# The C side of the function puts the number in r15
	mov %r15, %rax

	# We can now invoke the kernel and return
	syscall
	ret

.size __syscall, . - __syscall
