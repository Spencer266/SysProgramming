#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFSIZE 512

int pipefd[2];
pid_t pid;
char wmsg[BUFSIZE];
char rmsg[BUFSIZE];

void sig_handler(int sig)
{
	read(pipefd[0], rmsg, sizeof(rmsg));
	printf("Child caught signal %d, read: [%s]\n", sig, rmsg);
}

int main()
{
	int pipe_stat;
	signal(SIGUSR1, sig_handler);
	pipe_stat = pipe(pipefd);
	pid = fork();

	if (pid > 0) {
		printf("Parent process, child pid of %d\n", pid);
		while(1) {
			fgets(wmsg, BUFSIZE, stdin);
			wmsg[strcspn(wmsg, "\n")] = 0;
			if (strcmp(wmsg, "quit") == 0) {
				kill(pid, SIGINT);
				wait(NULL);
				exit(0);
			} else {
				write(pipefd[1], wmsg, sizeof(wmsg));
				kill(pid, SIGUSR1);
			}
		}
	}
	else if (pid == 0) {
		printf("Child process, parent pid of %d, pid of %d\n", getppid(), getpid());
		while(1);
	}
	return 0;
}
