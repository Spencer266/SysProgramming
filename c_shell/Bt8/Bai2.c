#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define CMDSIZ 32

void process_command(char *cmdbuf)
{
    int pid, sloc;
    pid = fork();
    char *args[] = {NULL};
    if (pid < 0)
        write(2, "no more processes\n", 18);
    else if (pid == 0)
    {
        if (execvp(cmdbuf, args) < 0)
        {
            write(2, "error\n", 6);
            exit(1);
        }
        else
        {
            wait(&sloc);
        }
    }
}

int main(int argc, char *argv[])
{
    int logout = 0, cmdsiz;
    char cmdbuf[CMDSIZ];
    while (!logout)
    {
        write(1, "myshell> ", 9);
        cmdsiz = read(0, cmdbuf, CMDSIZ);
        cmdbuf[cmdsiz - 1] = '\0';
        if (strcmp("logout", cmdbuf) == 0)
            ++logout;
        else
        {
            process_command(cmdbuf);
            wait(NULL);
        }
    }
    return 0;
}
