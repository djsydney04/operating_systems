#include <stdio.h>
#include <sys/semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

void *thread_function(void *arg);

#define WORK_SIZE 1024

/* Shared buffer: main writes lines here, the worker thread reads them.
   Global storage is zero-initialized, so the buffer starts empty. */
char work_area[WORK_SIZE];

sem_t *semid;

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;

    semid = sem_open("SEM", O_CREAT, 0664, 0);
    if (semid == SEM_FAILED)
    {
        perror("Semaphore creation failed");
        exit(EXIT_FAILURE);
    }


    /* Start the worker. NULL attributes means the default thread setup,
       and NULL argument means the worker receives no extra data. */
    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Input some text. Enter 'end' to finish\n");

    /* Keep reading lines until the user types "end".
       strncmp compares only the first 3 characters, so "end" matches
       even with the newline that fgets leaves in the buffer. */
    while (strncmp("end", work_area, 3) != 0) {
        fgets(work_area, WORK_SIZE, stdin);
        sem_post(semid);
    }

    printf("\nWaiting for thread to finish...\n");

    /* Block until the worker exits, then reclaim its resources. */
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Thread joined\n");
    // Have to close the semaphore :)
    sem_close(semid);
    sem_unlink("SEM");
    exit(EXIT_SUCCESS);
}

/* Worker: print the length of whatever is currently in the shared buffer
   until main stores "end". strlen counts the newline from fgets, so we
   subtract 1 to report the number of characters the user typed. */
void *thread_function(void *arg) {
    sem_wait(semid);
    while (strncmp("end", work_area, 3) != 0) {
        printf("You input %ld characters\n", strlen(work_area) - 1);
        sem_wait(semid);
    }
    pthread_exit(NULL);
}
