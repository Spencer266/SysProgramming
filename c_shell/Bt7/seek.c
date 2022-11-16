#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char buf[1];
	int countLine = 1;
	int f_inp = open("vd.txt", O_RDONLY, 0644);
	
	while (read(f_inp, buf, 1)) {
		if (countLine > 3) {
			write(1, buf, 1);
		}
		if (buf[0] == '\n') {
			countLine++;
		}
	}
	chmod("vd.txt", S_IRUSR | S_IRGRP);
	system("ls -l vd.txt");
	close(f_inp);
	return 0;
}
