    section .data

    section .text

	global transform

transform:
	push rbp	; push "calling procedure" frame pointer
	mov rbp, rsp	; set new frame pointer
			;	- "this procedure" frame pointer

;------------------------------------------------------------------------------

;------------------------------------------------------------------------------

	mov rsp, rbp	; restore original stack pointer
	pop rbp		; restore "calling procedure" frame pointer
	ret
