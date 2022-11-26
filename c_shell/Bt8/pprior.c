#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	pid_t pid, pida[10];
	int count = 0;
	pid = fork();
	pida[0] = pid;
	count++;

	for (int i = 1; i < 5; i++) {
		if (pid) {
			pid = fork();
			pida[i] = pid;
		}
		else {
			break;
		}
	}

	int prio = getpriority(PRIO_PROCESS, getpid());
	if (pid) {
    	wait(NULL);
		printf("Parent priority: %d\n", prio);
	}
	else {
		printf("Child priority: %d\n", prio);
		sleep(5);
	}
	return 0;
}
