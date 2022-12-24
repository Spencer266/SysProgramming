#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NBUF 5

int buf[NBUF];
int head, tail; // empty, full
int data, num_of_data;

pthread_mutex_t mutex;
pthread_cond_t empty, full;

void *in();
void *out();
void print_buf();

int main() {
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&full, NULL);

	for (int i = 0; i < NBUF; i++) {
		buf[i] = 0;
	}
	head = NBUF;
	tail = 0;
	data = 1;
	num_of_data = 12;

	pthread_t producer, consumer;
	pthread_create(&producer, NULL, in, NULL);
	pthread_create(&consumer, NULL, out, NULL);

	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&empty);
	pthread_cond_destroy(&full);
	return 0;
}

void *in() {
	int n = num_of_data;
	int next = 0;
	while (n > 0) {
		pthread_mutex_lock(&mutex);
		while (tail >= NBUF)
			pthread_cond_wait(&full, &mutex);
		buf[next] = data;
		head--;
		tail++;
		printf("Produced: ");
		print_buf();
		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&mutex);
		n--;
		next = (next+1) % NBUF;
		sleep(2);
	}
	pthread_exit(0);
}

void *out() {
	int n = num_of_data;
	int next = 0;
	while (n > 0) {
		pthread_mutex_lock(&mutex);
		while (head >= NBUF)
			pthread_cond_wait(&empty, &mutex);
		buf[next] = 0;
		head++;
		tail--;
		printf("Consumed: ");
		print_buf();
		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
		n--;
		next = (next+1) % NBUF;
		sleep(5);
	}
	pthread_exit(0);
}

void print_buf() {
	for (int i = 0; i < NBUF; i++) {
		if (buf[i] == 0) printf(". ");
		else printf("O ");
	}
	printf("\n");
}
