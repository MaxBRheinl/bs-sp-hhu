SECTION .bss
;	a resq 5

SECTION .data
	a: dq 0,0,0,0,0

SECTION .text
global _start

_start:
	mov rcx, 0

for_loop:
	cmp rcx, 5
	jge end
	
	mov [a+8*rcx], rcx
	
	inc rcx
	jmp for_loop

end:
	mov rax, 60
	mov rdi, 0
	syscall
