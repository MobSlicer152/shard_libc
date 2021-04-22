.code

; Move a value into r15
__move_to_r15 PROC
	; Move the first parameter to r15
	mov r15, rcx
	ret
__move_to_r15 ENDP
PUBLIC __move_to_r15

; The syscall function's core implementation
__syscall PROC
	; Put rcx in r10, it's what NTDLL's syscall gate does, I don't know why
	mov r10, rcx

	; The wrapper puts the number in r15
	mov rax, r15

	; We can now invoke the kernel and return
	syscall
	ret
__syscall ENDP
PUBLIC __syscall

END
