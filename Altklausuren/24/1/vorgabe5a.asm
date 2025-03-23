; nasm -g -f elf64 aufgabe5a.asm 
; ld -m elf_x86_64 aufgabe5a.o -o aufgabe5a

section .text
    global _start

_start:
    ; convert string
    ; *** Hier muss Code eingefuegt werden


    ; write to stdout
    ; *** Hier muss Code eingefuegt werden

    ; exit    
    mov rax, 60         ; syscall number for exit
    xor rdi, rdi        ; exit code 0
    syscall             ; exit successfully


section .data
    mystr db "betriebssysteme", 0 ; null-terminated string
