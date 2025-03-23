SECTION .data
	a dq 0
	b dq 7

SECTION .text
global _start
_start:
	mov rax, [a]
	cmp rax, 0
	jne else_case
	mov rax, 1
	mov [b], rax
	jmp end

else_case:
	mov rax, 0
	mov [b], rax

end:
	mov rax, 60
	mov rdi, 0
	syscall
