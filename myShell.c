#include <stdio.h>
#include <string.h>

#include "myshell.h"
#include "thread_worker.h"

/* Group 4, CPSC 351-03, Programming Assignment 1 */

#define INPUT_BUFFER_SIZE 1024

static void discardRemainingInput(const char *input)
{
	size_t inputLength = strlen(input);

	if (inputLength > 0 && input[inputLength - 1] != '\n') {
		int character;

		do {
			character = getchar();
		} while (character != '\n' && character != EOF);
	}
}

int main(void)
{
	char input[INPUT_BUFFER_SIZE];

	printf("Welcome to myShell\n");

	while (1) {
		ParsedCommand command;

		printf("==> ");
		fflush(stdout);

		if (fgets(input, sizeof(input), stdin) == NULL) {
			putchar('\n');
			break;
		}

		discardRemainingInput(input);
		command = parseCommand(input);

		if (command.argc == 0) {
			continue;
		}

		if (strcmp(command.argv[0], "exit") == 0 ||
			strcmp(command.argv[0], "quit") == 0) {
			printf("Thanks for using myShell!\n");
			break;
		}

		if (!isSupportedCommand(command.argv[0])) {
			printUnsupportedCommandError(command.argv[0]);
			continue;
		}

		(void)executeCommandInThread(&command);
	}

	return 0;
}
