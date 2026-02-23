#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

int n;                      // number of processes
volatile bool *choosing;    // choosing[i]
volatile int  *number;      // number[i]
int counter = 0;            // shared critical resource

int max_number() {
    int max = 0;
    for (int i = 0; i < n; i++) {
        int val = number[i];
        if (val > max) max = val;
    }
    return max;
}

void lock(int i) {
    choosing[i] = true;

    number[i] = 1 + max_number();

    choosing[i] = false;

    for (int j = 0; j < n; j++) {
        while (choosing[j]);  

        while (number[j] != 0 &&
              (number[j] < number[i] ||
              (number[j] == number[i] && j < i)));
    }
}

void unlock(int i) {
    number[i] = 0;
}

void* process(void* arg) {
    int i = *(int*)arg;

    for (int k = 0; k < 3; k++) {

        lock(i);

        // Critical section
        int local = counter;
        local++;
        counter = local;

        printf("Process %d in CS → Counter = %d\n", i, counter);

        unlock(i);
    }

    return NULL;
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    pthread_t *threads = calloc(n, sizeof(pthread_t));
    int *ids = calloc(n, sizeof(int));

    choosing = calloc(n, sizeof(bool));
    number   = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, process, &ids[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final Counter = %d\n", counter);

    free((void *)choosing);
    free((void *)number);
    free(threads);
    free(ids);

    return 0;
}