#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

volatile bool *flag;
volatile int turn = 0;
int counter = 0;

void* process(void* arg) {
    int i = *(int*)arg;
    int j = 1 - i;

    for (int k = 0; k < 5; k++) {
        flag[i] = true;
        turn = j;

        while (flag[j] && turn == j);

        // Critical section
        counter++;
        printf("Process %d in CS. Counter = %d\n", i, counter);

        flag[i] = false;
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int *id = calloc(2, sizeof(int));

    flag = calloc(2, sizeof(bool));

    id[0] = 0;
    id[1] = 1;

    pthread_create(&t1, NULL, process, &id[0]);
    pthread_create(&t2, NULL, process, &id[1]);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Counter = %d\n", counter);

    free((void *)flag);
    free(id);
    return 0;
}