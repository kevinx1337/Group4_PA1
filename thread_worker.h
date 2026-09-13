#ifndef THREAD_WORKER_H
#define THREAD_WORKER_H

#include "myshell.h"

void *commandThread(void *argument);

//rund one validated command on child thread
int executeCommandInThread(const ParsedCommand *command);

#endif
