    section .data
    srcwidth DD 0
    srcheight DD 0
    dstwidth DD 0
    dstheight DD 0
    rotationCos DQ 0.
    rotationSin DQ 0.
    translationX DD 0
    translationY DD 0
    temp DW 0
    size DD 0

    section .text

	global transform

transform:
	push rbp	; push "calling procedure" frame pointer
	mov rbp, rsp	; set new frame pointer
			;	- "this procedure" frame pointer

;------------------------------------------------------------------------------
    mov [srcwidth], rsi
    mov [srcheight], rdx
    mov [dstwidth], r8
    mov [dstheight], r9
    movsd [rotationCos], xmm0
    movsd [rotationSin], xmm1
    mov rax, [rbp+16]
    mov [translationX], rax
    mov rax, [rbp+24]
    mov [translationY], rax
    mov eax, [dstwidth]
    mov ebx, [dstheight]
    mul ebx
    mov ebx,4
    mul ebx
    mov [size],eax

    ;rdi- src start, rcx- dst
;------------------------------------------------------------------------------
    ;Loop to print picture into bitmap:
    mov ebx, [srcheight] ;max height
    dec ebx ; to remove
    mov r13,0 ;iterating Height

;rsi*r14+r12, rcx, rdi reserved!!!
height:
    mov esi, [srcwidth]
    mov r14,0 ;iterating Width
width:
    ;Calculating rotation coordinates x,y:
   ; movsd xmm0,[rotationCos]
    ;movsd xmm1, [rotationSin]
    ;cvtsi2sd xmm3,r14 ;width
    ;cvtsi2sd xmm4,r13 ;height

    mov r15,r14
    mov rax,r13
    mov edx,[srcwidth]
    mul edx
    add rax,r15
    mov edx,4
    mul edx
    mov r12,[rdi+rax]


     mov r15,r14
     add r15,[translationX]
     mov rdx,r15
     cmp edx,0
     jl check
     cmp edx,[dstwidth]
     jg check
     mov rax,r13
     add rax,[translationY]
     mov edx,[dstwidth]
     mul edx
     add rax,r15
     mov edx,4
     mul edx
     mov edx,[size]
     cmp eax,0
     jl check
     cmp eax,edx
     jg check
     mov [rcx+rax],r12
check:
    inc r14
    dec esi
    cmp esi,0
    jne width
    inc r13
    dec ebx
    cmp ebx,0
    jne height

	mov rsp, rbp	; restore original stack pointer
	pop rbp		; restore "calling procedure" frame pointer
	ret
