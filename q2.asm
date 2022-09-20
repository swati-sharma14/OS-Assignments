section .data
	n	dd 0
	text	times 100 db 0
	iformat	db "%d %s", 0
	oformat	db "%d %s", 0x0a, 0
	inp	db "Enter number and string: ", 0


section .text
	global main
	extern scanf
	extern printf


main:
	push rbp
	mov rbp, rsp

	mov rax, 0
	lea rdi, [inp]
	call printf

	lea rdi, [iformat]
	lea rsi, [n]
	lea rdx, [text]
	mov rax, 0
	call scanf

	lea rdi, [oformat]
	mov rsi, [n]
	lea rdx, [text]
	mov rax, 0
	call printf
	
	mov rax, 0
	pop rbp
	ret 
