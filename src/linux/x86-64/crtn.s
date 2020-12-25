.section .init
	# Indented because this is the end of _init
	popq %rbp
	ret

.section .fini
	# Indented because this is the end of _fini
	popq %rbp
	ret
