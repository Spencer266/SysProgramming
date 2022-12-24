#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

char *pattern;

void *grep(void *fpath);

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		printf("Missing argument\n");
		exit(0);
	} else if (argc == 2) {
		printf("Missing file paths to open\n");
		exit(0);
	}

	pattern = argv[1];
	pthread_t threads[10];

	for (int i = 0; i < argc - 2; i++) {
		pthread_create(&threads[i], NULL, grep, (void *)argv[i+2]);
	}

	for (int i = 0; i < argc - 2; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}

void *grep(void *fpath) {
	char *path = (char *)fpath;
	char buf[256];
	int count = 0;

	FILE *fp = fopen(path, "r");
	if (fp == NULL) {
		perror(path);
		pthread_exit((void *)1);
	}

	while (fgets(buf, 256, fp)) {
		if (strstr(buf, pattern)) {
			//printf("-> %s", buf);
			count++;
		}
	}
	printf("%s: %d occurences\n", path, count);
	pthread_exit(0);
}
