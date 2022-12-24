#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

struct foo {
	int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf("%s", s);
	printf(" structure at 0x%lx\n", (unsigned long)fp);
	printf(" foo.a = %d\n", fp->a);
	printf(" foo.b = %d\n", fp->b);
	printf(" foo.c = %d\n", fp->c);
	printf(" foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg)
{
	printf("thread 1: ID is %lu\n", (unsigned long)pthread_self());
	struct foo *fooo = (struct foo *)malloc(sizeof(struct foo));
	fooo->a = 1;
	fooo->b = 2;
	fooo->c = 3;
	fooo->d = 4;
	printfoo("thread1:\n", fooo);
	pthread_exit((void *)fooo);
}

void *thr_fn2(void *foo)
{
	printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
	printfoo("thread2:\n", (struct foo *)foo);
	pthread_exit((void *)foo);
}

int main(void)
{
	int err;
	pthread_t tid1, tid2;
	struct foo *fp;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		perror("Thread 1: ");
	err = pthread_join(tid1, (void *)&fp);
	if (err != 0)
		perror("Thread 1: ");
	sleep(1);

	printf("parent starting second thread\n");

	err = pthread_create(&tid2, NULL, thr_fn2, (void *)fp);
	if (err != 0)
		perror("Thread 2: ");
	err = pthread_join(tid2, (void *)&fp);
	if (err != 0)
		perror("Thread 2: ");
	sleep(1);

	printfoo("parent:\n", fp);
	free(fp);
	exit(0);
}
