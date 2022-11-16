#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char buf[1024];
	sprintf(buf, "cp -r %s %s", argv[1], argv[2]);
	system(buf);
	exit(0);
}
