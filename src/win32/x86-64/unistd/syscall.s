.section .text

# Move a value into r15
.global __move_to_r15
__move_to_r15:
	# Move the first parameter to r15
	mov %rcx, %r15
	ret

# The syscall function's core implementation
.global __syscall
__syscall:
	# Put rcx in r10, it's what NTDLL's syscall gate does, I don't know why
	mov %rcx, %r10

	# The wrapper puts the number in r15
	mov %r15, %rax

	# We can now invoke the kernel and return
	syscall
	ret
