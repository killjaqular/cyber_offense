#!/usr/bin/python3

import os,sys

file = sys.argv[1]
obj = file.rstrip('.nasm')+'.o'
bin = file.rstrip('.nasm')+'.bin'

cle='nasm -f elf64 '+file+' -o '+str(obj)
ldr='ld -N '+obj+' -o '+str(bin)

os.system(cle)
os.system(ldr)
