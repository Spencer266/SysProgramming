#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char dir[256];
	if (argc == 1)
		chdir("~");
	else
		chdir(argv[1]);
	getcwd(dir, 256);
	printf("%s\n", dir);
	exit(0);
}
