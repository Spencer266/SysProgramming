#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char buf[1];
	int fd = open(argv[1], O_RDONLY, 0644);
	if (fd < 0) {
		perror("fd");
		exit(EXIT_FAILURE);
	}
	while (read(fd, buf, 1)) {
		printf("%s", buf);
	}
	exit(0);
}
