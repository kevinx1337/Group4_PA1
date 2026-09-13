#ifndef MYSHELL_H
#define MYSHELL_H

#define MAX_ARGUMENTS 4

typedef struct {
    char *argv[MAX_ARGUMENTS];
    int argc;
} ParsedCommand;

ParsedCommand parseCommand(char *input);
int isSupportedCommand(const char *command);
void printUnsupportedCommandError(const char *command);
int executeCommandInThread(const ParsedCommand *command);
void *commandThread(void *argument);

#endif
