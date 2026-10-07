#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n;
    pid_t pid;

    if (argc != 2 || atoi(argv[1]) <= 0) {
        printf("Invalid input. Please add a single argument or a positive number.\n");
        return 1;
    }
    n = atoi(argv[1]);

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        return 1;
    }

    if (pid == 0) {
        printf("%d\n", n);
        while (n != 1) {
            if (n % 2 == 0) {
                n = n / 2;
            } else {
                n = 3 * n + 1;
            }
            printf("%d\n", n);
        }
    } else {
        wait(NULL);
    }
    return 0;
}
