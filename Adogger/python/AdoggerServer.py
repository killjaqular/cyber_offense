import socketserver

from sys import stdout

from EstablishConnection import AdoggerServer

def main():
    ################################################################
    # Start Server
    ################################################################
    HOST, PORT = "localhost", 9999
    with socketserver.TCPServer((HOST, PORT), AdoggerServer) as server:
        server.serve_forever()

    return

if __name__ == "__main__":
    main()
