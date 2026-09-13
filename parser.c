#include <string.h>

#include "myshell.h"

/* Group 4, CPSC 351-03, Programming Assignment 1 */

ParsedCommand parseCommand(char *input)
{
    ParsedCommand command = {{NULL}, 0};
    char *token;

    /* A NULL input has no command or arguments to parse. */
    if (input == NULL) {
        return command;
    }

    /* strtok skips leading delimiters and combines repeated whitespace. */
    token = strtok(input, " \t\n");

    /* Store at most the four arguments available in ParsedCommand. */
    while (token != NULL && command.argc < MAX_ARGUMENTS) {
        command.argv[command.argc] = token;
        command.argc++;
        token = strtok(NULL, " \t\n");
    }

    return command;
}
