#include <stdio.h>
#include <limits.h>
#include <pthread.h>

struct row_info {
    short row_no;
    short *row_vals;
};

short max = SHRT_MIN;

pthread_mutex_t mutex;

void *sum_row(void *m_row) {
    struct row_info *row = (struct row_info *)m_row;
    short row_max = SHRT_MIN;
    for (int i = 0; i < 5; i++) {
        if (*(row->row_vals + i) > row_max)
        	row_max = *(row->row_vals + i);
    }

    pthread_mutex_lock(&mutex);
    if (row_max > max)
    	max = row_max;
    pthread_mutex_unlock(&mutex);
}

int main() {
    short matrix[5][5] = {
        {1, 19, 12, -1, -6},
        {9, 7, 5, 3, -4},
        {7, 2, 4, 9, -3},
        {-4, 7, 8, -2, 5},
        {2, -5, -4, 12, 7}
    };
    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[5];
    struct row_info args[5];

    for (int i = 0; i < 5; i++) {
        args[i].row_no = i;
        args[i].row_vals = matrix[i];
        pthread_create(&threads[i], NULL, sum_row, (void *)&args[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Lon nhat: %hi\n", max);
    return 0;
}
