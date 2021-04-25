.code

__get_peb PROC
	mov rax, QWORD PTR gs:[60h]
	ret
__get_peb ENDP
PUBLIC __get_peb

END
