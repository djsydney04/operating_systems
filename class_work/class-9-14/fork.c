#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid;
        /*fork a child process*/
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            return 1;
        }
        if (pid == 0) {
            /*child process*/
            execlp("/bin/ls", "ls", "-l", NULL);
        }
        else { /*parent process*/
            wait(NULL);
            printf("Child process completed\n");
        }
}
