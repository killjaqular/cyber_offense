#/usr/bin/python3

from sys import argv, stdout

shellCode = open(argv[1], 'r')
shellCode = shellCode.read().split("\n")

SHELL_LENGTH = shellCode[0]
SHELL_CODE   = ""

for byte in shellCode[1:]:
    SHELL_CODE += f'0x{byte},'

SHELL_CODE = SHELL_CODE[0:-4]

encoderTemplate = \
'''
global _start

segment .data

    key equ       0xb3
    length equ    ''' + SHELL_LENGTH +\
'''
    shellcode: db ''' + SHELL_CODE +\
'''

section .text

_start:

    lea rsi, [shellcode]
    mov rcx, 0x00

    xor_loop:
        mov al,  byte [rsi+rcx]
        xor al,  key
        mov byte [rsi+rcx], al
        inc rcx
        cmp rcx, length
        jne xor_loop

    lea rsi, [shellcode]
    mov rdi, 0x01
    lea rdx, [length]
    mov rax, 0x01
    syscall

    mov rbx, 0x00
    mov rax, 0x3c
    syscall
'''

stdout.write(f'{encoderTemplate}\n')

output = open('asm/encoderWithPayload.asm', 'w')
output.write(encoderTemplate)
