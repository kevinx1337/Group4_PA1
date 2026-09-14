# Group4_PA1

1. Student/Group Information

Course/Section: CPSC 351-03
Assignment: Command Line Interpreter (myShell)

Group Members:
- Kevin Xiao
- Saif Al Habashneh
- Erik Elizarraras
- Bhavesh Malhi
- Jimmy Williams


2. Files Included

- myShell.c
- myshell.h
- parser.c
- cmd_validation.c
- thread_worker.c
- thread_worker.h
- README.txt


3. How to Compile

gcc -Wall -Wextra -pedantic myShell.c parser.c cmd_validation.c thread_worker.c -pthread -o myShell


4. How to Run

./myShell

Use `exit` or `quit` to close the shell.


5. Supported Commands

Unix/Linux/POSIX:
ls, man, df, path, ps, echo, ping

Windows:
dir, help, vol, path, tasklist, notepad, echo, color, ping

Command validation is case-sensitive.


6. Threading Design

Valid commands are executed in a child thread using pthread_create().
The parent waits for the command to finish using pthread_join() before
displaying the next prompt.


7. Testing

Verified:
- echo Hello
- ls
- ping -c 1 127.0.0.1
- invalid command handling
- case-sensitive command validation
- quit/exit handling


8. Known Limitations

- Maximum of four command-line tokens.
- Extra tokens are ignored.
- Quoted strings with spaces are not specially handled.
- Only whitelisted commands are accepted.


9. Team Contributions

- Person 1: Core shell loop and integration.
- Person 2: Command parsing.
- Person 3: Command validation.
- Person 4: Threading and synchronization.
- Person 5: Testing, screenshots, and README.


10. Screenshots / Evidence

- Screenshot 1 — screenshots/01_testing.png:
  Shows valid command execution, invalid-command handling, ping with arguments,
  and quit/closing behavior.