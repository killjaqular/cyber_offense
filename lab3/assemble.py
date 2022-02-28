#!/usr/bin/python3

import os, sys

file = sys.argv[1]
obj  = file.rstrip('.nasm')+'.o'
bin  = file.rstrip('.nasm')+'.bin'
bin  = 'encodedBinaries' + bin[3:]
cle  = 'nasm -f elf64 '+ file + ' -o ' + str(obj)
ldr  = 'ld -N ' + obj + ' -o ' + str(bin)

os.system(cle)
os.system(ldr)
os.system("./encodedBinaries/encoderWithPayload.bin | xxd -i > temp")

temp = open('temp', 'br')
temp = str(temp.read()[2:])[2:-3].split("\\n")

temp2 = []

for every in temp:
    temp2.append(every.split(", "))

temp = []

for someList in temp2:
    for element in someList:
        temp.append(element.replace(',', '').replace(' ', '')[2:])

output = open('shellcodeForDecoder', 'w')

for index in range(len(temp)):
    output.write(f'0x{temp[index]}')
    if index != len(temp) - 1:
        output.write(f',')
