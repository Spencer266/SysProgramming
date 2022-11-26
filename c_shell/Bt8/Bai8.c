#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define MAXLINE 256

static void sig_alrm(int);
static jmp_buf env_alrm;

int main(void)
{
	int n;
	char line[MAXLINE];
	signal(SIGALRM, sig_alrm);
	alarm(10);
	if (setjmp(env_alrm) != 0) {
		printf("read timeout\n");
		exit(2);
	}
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
		perror("Read error: ");
		exit(1);
	}
 	write(STDOUT_FILENO, line, n);
 	exit(0);
}

static void sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}
