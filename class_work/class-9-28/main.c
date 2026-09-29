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
    pthread_t tid[3]