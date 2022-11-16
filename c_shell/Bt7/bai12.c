#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>

struct stat mystat, *sp;
char *t1 = "xwrxwrxwr-------";
char *t2 = "----------------";
int ls_file(char *fname)
{
    struct stat fstat, *sp;
    int r, i;
    char ftime[64];
    sp = &fstat;
    if ((r = lstat(fname, &fstat)) < 0)
    {
        printf("can.t stat %s\n", fname);
        exit(1);
    }
    if ((sp->st_mode & 0xF000) == 0x8000)
        printf("-");
    if ((sp->st_mode & 0xF000) == 0x4000)
        printf("d");
    if ((sp->st_mode & 0xF000) == 0xA000)
        printf("l");
    for (i = 8; i >= 0; i--)
    {
        if (sp->st_mode & (1 << i))
            printf("%c", t1[i]);
        else
            printf("%c", t2[i]);
	}

    printf("%2li ", sp->st_nlink);
    printf("%s ", getpwuid(sp->st_uid)->pw_name);
    printf("%s ", getgrgid(sp->st_gid)->gr_name);
    
	printf("%6li ", sp->st_size);
    strcpy(ftime, ctime(&sp->st_ctime));
    ftime[strlen(ftime) - 1] = 0;
    printf("%s ", ftime);
    printf("%s", basename(fname));
	printf("\n");
}

int ls_dir(char *dname)
{
	DIR *dir;
    struct dirent *dirp;
	char path[256];
	
	dir = opendir(dname);
	while ((dirp = readdir(dir))) {
		strcpy(path, dname);
		strcat(path, "/");
		strcat(path, dirp->d_name);
		ls_file(path);
	}
}

int main(int argc, char *argv[])
{
    struct stat mystat, *sp = &mystat;
    int r;
    char *filename, path[1024], cwd[256];
    filename = "./";
    if (argc > 1)
        filename = argv[1];
    if (r = lstat(filename, sp) < 0)
    {
        printf("no such file %s\n", filename);
        exit(1);
    }
    strcpy(path, filename);
    if (path[0] != '/')
    {
        getcwd(cwd, 256);
        strcpy(path, cwd);
        strcat(path, "/");
        strcat(path, filename);
    }
    if (S_ISDIR(sp->st_mode))
        ls_dir(path);
    else
        ls_file(path);
	return 0;
}
