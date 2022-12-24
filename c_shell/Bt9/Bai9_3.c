#include <stdio.h>
#include <pthread.h>

int arr_size = 15;
int arr[15] = {4, 7, 5, 11, 0, 16, 2, 10, 1, 20, 9, 3, 6, 8, 12};

struct bounding {
	int upper;
	int lower;
};

void *qsort(void *bound);
void swap(int *a, int *b);

int main() {
	pthread_t thread;
	struct bounding bounder;
	bounder.lower = 0;
	bounder.upper = arr_size - 1;
	pthread_create(&thread, NULL, qsort, (void *)&bounder);
	pthread_join(thread, NULL);

	for (int i = 0; i < arr_size; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void *qsort(void *bounder) {
	struct bounding *bound = (struct bounding *)bounder;
	if (bound->upper == bound->lower) pthread_exit(0);
	if (bound->upper - bound->lower == 1) {
		if (arr[bound->upper] < arr[bound->lower]) swap(&arr[bound->upper], &arr[bound->lower]);
		pthread_exit(0);
	}

	int small_ind = bound->lower - 1;
	//int pivot_ind = bound->lower + (bound->upper - bound->lower)/2;
	int pivot_ind = bound->lower + 1;
	int pivot = arr[pivot_ind];

	for (int i = bound->lower; i <= bound->upper; i++) {
		if (arr[i] < pivot) {
			swap(&arr[++small_ind], &arr[i]);
		}
		if (arr[i] == pivot) {
			pivot_ind = ++small_ind;
			swap(&arr[small_ind], &arr[i]);
		}
	}

	if (small_ind == bound->lower - 1) small_ind++;
	swap(&arr[small_ind], &arr[pivot_ind]);
	pivot_ind = small_ind;

	struct bounding left, right;
	left.lower = bound->lower;
	left.upper = pivot_ind - 1;
	right.lower = pivot_ind + 1;
	right.upper = bound->upper;

	pthread_t th_left, th_right;
	if (pivot_ind > bound->lower) pthread_create(&th_left, NULL, qsort, (void *)&left);
	if (pivot_ind < bound->upper) pthread_create(&th_right, NULL, qsort, (void *)&right);

	pthread_join(th_left, NULL);
	pthread_join(th_right, NULL);
	pthread_exit(0);
}
