#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>   
#include <string.h>   

#include "thread_worker.h"

/* Group 4, CPSC 351-03, Programming Assignment 1 */
/* Threading and synchronization (POSIX / Linux, pthreads). */

#define COMMAND_LINE_SIZE 1024

//Everything the child thread needs, passed as pthread_create()'s single void * argument. No globals are used
typedef struct {
    ParsedCommand command;  /* private copy of the parsed, validated command */
    int status;             /* written by the child, read by the parent */
} ThreadArgument;

/*
 * parseCommand() split the user's input into argv. system() takes a single string.
 * Returns 0 on success or -1 if result would not fit in 'buffer'.
 */
static int buildCommandLine(const ParsedCommand *command, char *buffer, size_t size)
{
    size_t used = 0;
    int i;

    if (command == NULL || buffer == NULL || size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    for (i = 0; i < command->argc; i++) {
        size_t tokenLength = strlen(command->argv[i]);
        size_t needed = tokenLength + (i > 0 ? 1 : 0);  /* +1 for the space */

        if (used + needed + 1 > size) {
            return -1;  /* refuse to overflow the buffer */
        }

        if (i > 0) {
            buffer[used++] = ' ';
        }

        memcpy(buffer + used, command->argv[i], tokenLength);
        used += tokenLength;
        buffer[used] = '\0';
    }

    return 0;
}

// Child thread body.
 
void *commandThread(void *argument)
{
    ThreadArgument *work = (ThreadArgument *)argument;
    char commandLine[COMMAND_LINE_SIZE];

    if (work != NULL) {
        if (buildCommandLine(&work->command, commandLine, sizeof(commandLine)) != 0) {
            fprintf(stderr, "myShell: command line is too long to execute\n");
            work->status = -1;
        } else {
            // system() hands the line to /bin/sh -c and waits for it.
              
            work->status = system(commandLine);

            if (work->status == -1) {
                perror("myShell: system");
            }
        }
    }

    // The parent passes NULL to pthread_join().
    
    return NULL;
}

//Parent-side dispatch: one child thread per valid command.
int executeCommandInThread(const ParsedCommand *command)
{
    ThreadArgument work;
    pthread_t threadId;
    int createResult;
    int joinResult;

    if (command == NULL || command->argc == 0) {
        return -1;
    }
    work.command = *command;
    work.status  = -1;

    createResult = pthread_create(&threadId, NULL, commandThread, &work);
    if (createResult != 0) {
        // pthread_* functions return the error number directly
        fprintf(stderr, "myShell: pthread_create failed: %s\n",
                strerror(createResult));
        return -1;
    }

    /* SYNCHRONIZATION: pthread_join() blocks this parent thread until the
       child terminates. Also reclaims the child's resources. */
    joinResult = pthread_join(threadId, NULL);
    if (joinResult != 0) {
        fprintf(stderr, "myShell: pthread_join failed: %s\n",
                strerror(joinResult));
        return -1;
    }

    return work.status;
}
