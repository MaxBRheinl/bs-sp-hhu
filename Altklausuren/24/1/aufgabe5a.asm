; nasm -g -f elf64 aufgabe5a.asm 
; ld -m elf_x86_64 aufgabe5a.o -o aufgabe5a

section .text
    global _start

_start:
    ; convert string
    ; *** Hier muss Code eingefuegt werden
    mov rcx, 0

loop_start:
	cmp rcx, 15
	jge print
	 
	mov rax, [mystr+rcx]
	sub rax, 32
	mov [mystr+rcx], rax
	
	inc rcx
	jmp loop_start
	

print:
    ; write to stdout
    ; *** Hier muss Code eingefuegt werden
    mov rax, 1
    mov rdi, 0
    mov rsi, mystr
    mov rdx, 16
    syscall

    ; exit    
    mov rax, 60         ; syscall number for exit
    xor rdi, rdi        ; exit code 0
    syscall             ; exit successfully


section .data
    mystr db "betriebssysteme", 0 ; null-terminated string
