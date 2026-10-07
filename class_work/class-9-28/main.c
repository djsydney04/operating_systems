#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


float average;
int max, min;
int nargs;

void *calculate_average(void *arg);
void *calculate_max(void *arg);
void *calculate_min(void *arg);

int main(int argc, char *argv[]) {
    pthread_t tid[3];

    int arr[32];
    nargs = argc - 1;
    for (int i = 0; i < nargs; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    pthread_create(&tid[0], NULL, calculate_average, arr);
    pthread_create(&tid[1], NULL, calculate_max, arr);
    pthread_create(&tid[2], NULL, calculate_min, arr);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    printf("Average: %f\n", average);
    printf("Max: %d\n", max);
    printf("Min: %d\n", min);
    return 0;
}

void *calculate_average(void *arg) {
    int sum = 0;
    int *arr = (int *)arg;
    for (int i = 0; i < nargs; i++) {
        sum += arr[i];
    }
    average = (float)sum / nargs;
    return NULL;
}

void *calculate_max(void *arg) {
    int *arr = (int *)arg;
    max = arr[0];
    for (int i = 1; i < nargs; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    return NULL;
}

void *calculate_min(void *arg) {
    int *arr = (int *)arg;
    min = arr[0];
    for (int i = 1; i < nargs; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return NULL;
}