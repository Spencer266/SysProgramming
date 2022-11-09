#include <stdio.h>
#include <stdlib.h>

int main() {
	char buf[256];
	char *res = realpath("hello.c", buf);
	if (res) {
		printf("File path: %s\n", buf);
	}
	else {
		perror("realpath");
		exit(EXIT_FAILURE);
	}
	exit(0);
}
