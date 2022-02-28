#/usr/bin/python3

from sys import stdout

SHELL_CODE = open('shellcodeForDecoder', 'r')
SHELL_CODE = SHELL_CODE.read()

decoderTemplate = \
'''
global _start

section .text

_start:
    jmp short exec_shellcode

start_decoding:
    pop rsi
    mov rcx, 0x00

    xor_loop:
        mov al, byte [rsi+rcx]
        xor al, 0xb3
        mov byte [rsi+rcx], al
        inc rcx
        cmp rcx, 121
        jne xor_loop

    jmp rsi

exec_shellcode:
    call start_decoding
    shellcode: db ''' + SHELL_CODE + "\n"

stdout.write(f'{decoderTemplate}\n')

output = open('readyBins/decoderWithPayload.asm', 'w')
output.write(decoderTemplate)
