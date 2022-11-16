#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	close(1);
    int fdout = open("vidu.doc", O_WRONLY | O_CREAT, 0644);

    if (argc <= 1) {
        char *line = NULL;
        size_t size;
        ssize_t lineSize;
        while ((lineSize = getline(&line, &size, stdin))) {
            write(fdout, line, lineSize);
        }
        exit(0);
    }
    else {
        close(0);
        int fdin = open(argv[1], O_RDONLY);
        int nbytes;
        char buf[1024];
        if (fdin < 0) exit(1);
        while (nbytes = read(fdin, buf, 1024)) {
            write(fdout, buf, nbytes);
        }
        close(fdin);
    }
    close(fdout);
    exit(0);
}
