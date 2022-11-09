#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	char buf[256];
	int count = 0;
	fp = fopen(argv[2], "r");

	if (fp == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	while (fgets(buf, 256, fp)) {
		if (strstr(buf, argv[1])) {
			printf("-> %s", buf);
			count++;
		}
	}
	printf("%d occurences\n", count);
	exit(0);
}
