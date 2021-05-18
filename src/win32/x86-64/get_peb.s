.section .text

.global __get_peb
__get_peb:
	mov %gs:0x60, %rax # PEB
	ret
