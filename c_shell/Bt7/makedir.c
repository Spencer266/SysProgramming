#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Hay them ten thu muc de tao!\n");
	}
	else {
		int r;
		for (int i = 1; i < argc; i++) {
			r = mkdir(argv[i], 0766);
			if (r < 0) {
				printf("Input khong hop le: %s\n", strerror(errno));
				//perror("mkdir");
				exit(EXIT_FAILURE);
			}
		}
	}
	system("ls -la");
	exit(0);
}
