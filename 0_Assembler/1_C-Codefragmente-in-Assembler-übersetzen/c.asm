SECTION .bss

SECTION .data
	i dq 10
	ergebnis dq 1

SECTION .text
global _start

_start:
	
while_loop:
	mov rcx, [i]
	dec rcx
	mov [i], rcx
	cmp rcx, 0
	je end
	
	mov rax, [ergebnis]
	mul rcx
	mov [ergebnis], rax
	jmp while_loop
	

end:
	mov rax, 60
	mov rdi, 0
	syscall
