from sys import stdout
import socketserver

class AdoggerServer(socketserver.BaseRequestHandler):
    def handle(self):
        stdout.write(f'handle() called:_> ')
        self.lastMessage = self.request.recv(1024).rstrip()
        stdout.write(f'{self.lastMessage}\n')
