SECTION .bss

SECTION .data
	filename db 'testfile.txt', 0
	message db 'Hello, World!', 10, 0
	fd dq 0
SECTION .text
global _start
_start:
	mov rax, 85
	mov rdi, filename
	mov rsi, 0o644
	syscall
	
	cmp rax, 0
	jl failed_end
	
	mov [fd], rax
	
	mov rax, 1
	mov rdi, [fd]
	mov rsi, message
	mov rdx, 14
	syscall
	
	mov rax, 3
	mov rdi, [fd]
	syscall
	
end:
	mov rax, 60
	mov rdi, 0
	syscall
	
	
failed_end:
	mov rax, 60
	mov rdi, 1
	syscall
