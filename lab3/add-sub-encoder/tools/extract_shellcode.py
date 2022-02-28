import os, sys

print("\n------------- Shellcode --------------------")
cmd = "objdump -d "+str(sys.argv[1])+" | grep -Po '\\s\\K[a-f0-9]{2}(?=\\s)' | sed 's/^/\\\\x/g' | perl -pe 's/\r?\\n//' | sed 's/$/\\n/'"
os.system(cmd)
