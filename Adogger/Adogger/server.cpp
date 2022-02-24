#include <iostream>
#include <ws2tcpip.h>

#pragma commnet (lib, "ws2_32.lib")

using namespace std;

void main() {

	// Initialize winsock
	WSADATA wsDATA;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	
	if (wsOK != 0) {
		cerr << "Can't initialize winsock!" << endl;
		return;
	}

	// Create socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create socket!" << endl;
		return;
	}

	// Bind socket to IP address and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.s_un.s_addr = INADDR_ANY;

	bind(listening, (sockaddr*) &hint, sizeof(hint));

	// Tell winsock the socket is for listening
	listen(listening, SOMAXCONN);

	// Wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*) &client, &clientsize);

	if (clientSocket == INVALID_SOCKET) {
		cerr << "Client Socket error!" << endl;
		return;
	}

	char host[NI_MAXHOST];		// Client's remote name
	char service[NI_MAXHOST];	// Service Port for client

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	// Close listening socket

	// While loop: accept and echo message back to client

	// Close socket

	// Shutdown winsock

}
