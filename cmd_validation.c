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

/*
 * Command validation is OS-specific and check is case-sensitive
 */
int isSupportedCommand(const char *command) {
    if (command == NULL || strlen(command) == 0) {
        return 0;
    }

#ifdef _WIN32
    for (int i = 0; i < totalWindowsCmd; i++) {
        if (strcmp(command, windowsEnvironment[i]) == 0) {
            return 1;
        }
    }

#else
    for (int i = 0; i < totalUnixCmd; i++) {
        if (strcmp(command, unixEnvironment[i]) == 0) {
            return 1;
        }
    }
#endif

    return 0;
}

void printUnsupportedCommandError(const char *command) {
    if (command == NULL || strlen(command) == 0) {
        return;
    }

    printf("'%s' is not a supported command. Please try again.\n", command);
}
