#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Thieu doi so ten file de dem!\n");
		exit(0);
	}
	int fd, words, bytes, lines, wordCheck;
	int s_words = 0, s_bytes = 0, s_lines = 0;
	char buf[1];
	for (int i = 1; i < argc; i++) {
		words = 0;
		bytes = 0;
		lines = 0;
		fd = open(argv[i], O_RDONLY, 0644);
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
			else {
				wordCheck = 1;
			}
			bytes++;
		}
		printf("%d\t%d\t%d\t%s\n", lines, words, bytes, argv[i]);
		s_words += words;
		s_bytes += bytes;
		s_lines += lines;
		close(fd);
	}
	if (argc > 2) 
		printf("%d\t%d\t%d\tTong\n", s_lines, s_words, s_bytes);
	exit(0);
}

