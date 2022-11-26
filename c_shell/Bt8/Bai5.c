#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int target;

void CUSTOM_HANDLER(int);
void KILL_SELF(int);

int main (int argc, char *argv[])
{
	target = atoi(argv[1]);
	signal(SIGUSR1, CUSTOM_HANDLER);
	signal(SIGINT, KILL_SELF);
	while(1) {
		pause();
	}
	return 1;
}

void CUSTOM_HANDLER(int signum)
{
	if (kill(target, SIGHUP) < 0)
		printf("Process already killed\n");
	else
		printf("%d killed\n", target);
}

void KILL_SELF(int signum)
{
	printf("\nTerminated by signal %d\n", signum);
	exit(1);
}
