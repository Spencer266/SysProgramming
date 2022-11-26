#include <stdio.h>
#include <signal.h>
#include <math.h>
#include <stdlib.h>

void SIGNAL_HANDLER(int sig) {
	printf("Invalid arguments. Exiting...\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	signal(SIGTSTP, SIGNAL_HANDLER);
	double a, b;
	a = atof(argv[1]);
	b = atof(argv[2]);
	if (-(a*b) < 0 || (a == 0 && b != 0))
		raise(SIGTSTP);
	if (b == 0) 
		printf("Nghiem kep x = 0\n");
	else
		printf("Nghiem x1 = +-%.3f\n", sqrt(-b/a));
	exit(0);
}
