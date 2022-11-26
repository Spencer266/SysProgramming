#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void HANDLER(int sig)
{
	printf("Working...\n");
}
int main(int argc, char *argv[])
{
	int interval, m_interval = 0;
	if (argc <= 1) {
		printf("Set timer interval: ");
		scanf("%d", &interval);
	} else {
		interval = atoi(argv[1]);
		if (argc == 3)
			m_interval = atoi(argv[2]);
	}
	struct itimerval timer, oldtimer;
	signal(SIGALRM, HANDLER);
	timer.it_value.tv_sec = interval;
	timer.it_value.tv_usec = m_interval;
	timer.it_interval.tv_sec = interval;
	timer.it_interval.tv_usec = m_interval;
	setitimer(ITIMER_REAL, &timer, &oldtimer);
	while(1);
}

