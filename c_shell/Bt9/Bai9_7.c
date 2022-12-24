#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct fileWC {
	int words;
	int bytes;
	int lines;
};
struct fileWC total = { .words = 0, .bytes = 0, .lines = 0 };
pthread_mutex_t mutex;

void *wc(void *path);

int main (int argc, char *argv[]) {
	if (argc < 2) {
		printf("Missing file path to operate!\n");
		exit(0);
	}
	pthread_mutex_init(&mutex, NULL);
	pthread_t threads[10];
	for (int i = 0; i < argc - 1; i++) {
		pthread_create(&threads[i], NULL, wc, argv[i+1]);
	}

	for (int i = 0; i < argc - 1; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("%d\t%d\t%d\ttotal\n", total.lines, total.words, total.bytes);
	pthread_mutex_destroy(&mutex);
	return 0;
}

void *wc(void *p) {
	char *path = (char *)p;
	struct fileWC result;
	int fd = open(path, O_RDONLY, 0644);
	int words, bytes, lines, wordCheck;
    char buf[1];
    words = 0;
    bytes = 0;
    lines = 0;

    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    while (read(fd, buf, 1)) {
        if (buf[0] == '\n') {
            lines++;
            if (wordCheck == 1) words++;
            wordCheck = 0;
        }
        else if (buf[0] == ' ') {
            if (wordCheck == 1) words++;
            wordCheck = 0;
        }
        else
        	wordCheck = 1;
        bytes++;
    }
    printf("%d\t%d\t%d\t%s\n", lines, words, bytes, path);
    pthread_mutex_lock(&mutex);
    total.words += words;
    total.lines += lines;
    total.bytes += bytes;
    pthread_mutex_unlock(&mutex);
	pthread_exit((void *) &result);
}
