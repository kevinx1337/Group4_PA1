#include <stdio.h>
#include <string.h>
#include "myshell.h"

/* Group 4, CPSC 351-03, Programming Assignment 1 */

const char *windowsEnvironment[] = {
    "dir", "help", "vol", "path", "tasklist", "notepad", "echo", "color", "ping"
};

const char *unixEnvironment[] = {
    "ls", "man", "df", "path", "ps", "echo", "ping"
};

const int totalWindowsCmd = sizeof(windowsEnvironment) / sizeof(windowsEnvironment[0]);
const int totalUnixCmd = sizeof(unixEnvironment) / sizeof(unixEnvironment[0]);

int isSuppertedCommand(const char *command) {
    if (command == NULL || strlen(command) == 0) {
        return 0;
    }

    for (int i = 0; i < totalWindowsCmd; i++) {
        if (strcmp(command, windowsEnvironment[i]) == 0) {
            return 1;
        }
    }

    for (int k = 0; k < totalUnixCmd; k++) {
        if (strcmp(command, unixEnvironment[k]) == 0) {
            return 1;
        }
    }

    return 0;
}

void printUnsupportedCommandError(const char *command) {
    if (command == NULL || strlen(command) == 0) {
        return;
    }

    printf("'%s' is not a supported command. Please try again.\n", command);
}
