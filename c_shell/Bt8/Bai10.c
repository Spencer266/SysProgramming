#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

pid_t pid;

void HANDLE_SIG(int sig) {
	if (pid > 0)
		printf("Parent process caught signal %d\n", sig);
	else if (pid == 0)
		printf("Child process caught signal %d\n", sig);
	else
		printf("Error");
	exit(0);
}

int main() {
	signal(SIGALRM, HANDLE_SIG);
	pid = fork();

	/*if (pid > 0) {
		//alarm(5);
	}
	else {
		alarm(5);
	}*/
	alarm(5);
	while(1);
}
