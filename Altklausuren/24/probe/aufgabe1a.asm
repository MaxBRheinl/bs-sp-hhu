;
; nasm -g -f elf64 aufgabe1a.asm 
; ld -m elf_x86_64 aufgabe1a.o -o aufgabe1a
;
section .data
    filepath db "/proc/meminfo", 0 ; Null-terminated file path

section .bss
    buffer resb 4096               ; Buffer 

section .text
    global _start

_start:
    ;
    ; Open file
    ;
    mov rax, 2          ; syscall number for 'open'
    lea rdi, [filepath] ; pointer to file path
    mov rsi, 0          ; read-only mode (O_RDONLY)
    syscall             ; make the system call
    ; *** Code must be inserted here *** 
    ; Check if file was opened successfully
    cmp rax, 0
    je exit_error
    
    ;
    ; Read from file, see also "man read"
    ;
    ; *** Code must be inserted here *** 
    mov rdi, rax        ; 1. param: file descriptor
    mov rsi, buffer     ; 2. param: pointer to buffer
    mov rdx, 4096       ; 3. param: number of bytes to read
    mov rax, 0          ; syscall number for read
    syscall             ; make the system call
    ; *** Code must be inserted here *** 
    ; Check if read was successful
	cmp rax, 0
	jl exit_error
    
    ;
    ; Write to stdout
    ;
    mov rsi, buffer     ; pointer to buffer
    mov rdx, rax        ; len
    mov rax, 1          ; syscall number for write
    mov rdi, 1          ; file descriptor (stdout)
    syscall             ; make the system call
    ; *** Code must be inserted here *** 

exit_error:
    ; *** Code must be inserted here ***
    mov rax, 60
    mov rdi, 1
    syscall 


exit_success:
    mov rax, 60         ; syscall number for exit
    xor rdi, rdi        ; exit code 0
    syscall             ; exit successfully
