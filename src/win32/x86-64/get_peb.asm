.code

; Get the PEB's address
__get_peb PROC
	mov rax, gs:[60h] ; PEB offset
	ret
__get_peb ENDP
PUBLIC __get_peb

END
