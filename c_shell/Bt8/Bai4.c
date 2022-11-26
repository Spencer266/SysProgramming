#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int pipefds[2];
char wmsg[BUFSIZ];
pid_t pid;
void pipedo()
{
	pid = fork();
	if (pid == 0)
	{
		char rmsg[BUFSIZ];
		read(pipefds[0], rmsg, sizeof(rmsg));
		printf("Child Process: Reading from pipe [%s]\n", rmsg);
		exit(0);
	} else {
		printf("Parent Process: Writing to pipe [%s]\n", wmsg);
		write(pipefds[1], wmsg, sizeof(wmsg));
		wait(NULL);
	}
}
int main()
{
	int status;
	status = pipe(pipefds);
	if (status == -1)
	{
		printf("Unable to create pipe\n");
		exit(1);
	}
	printf("Enter the msg to write into Pipe\n");
	printf("To exit type \"quit\" \n");
	fgets(wmsg, BUFSIZ, stdin);
	wmsg[strcspn(wmsg, "\n")] = 0;
	while (strcmp(wmsg, "quit") != 0) 
	{
		pipedo();
		fgets(wmsg, BUFSIZ, stdin);
		wmsg[strcspn(wmsg, "\n")] = 0;
	}
	close(pipefds[0]);
	close(pipefds[1]);
	exit(0);
}
