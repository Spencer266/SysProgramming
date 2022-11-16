#include <stdio.h>
#include <unistd.h>

int main()
{ 
	int pid;
	printf("THIS IS %d MY PARENT=%d\n", getpid(), getppid());
	pid = fork();
	if (pid) {
		printf("THIS IS PROCESS %d CHILD PID=%d\n", getpid(), pid);
		sleep(10);
	} else {
		printf("this is process %d parent=%d\n", getpid(), getppid());
		sleep(10);
	}
	return 0;
}
