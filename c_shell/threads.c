#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *customThreadFunc() {
	printf("This is my custom thread!\n");
	return NULL;
}

int main() 
{
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, customThreadFunc, NULL);
	pthread_create(&thread2, NULL, customThreadFunc, NULL);
	if (pthread_equal(thread1, thread2))
		printf("Two threads are equal\n");
	else
		printf("Two threads are not equal\n");
	return 0;
}

