#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int n;

    if (argc != 2 || atoi(argv[1]) < 0) {
        printf("Invalid input. Please add a single argument or a positive number.\n");
        return 1;
    }
    n = atoi(argv[1]);
    while (n != 1){
        if (n % 2 == 0) {
            n = n / 2;
            printf("%d\n", n);
        } else {
            n = 3 * n + 1;
            printf("%d\n", n);
        }
    }
    printf("1\n Completed!\n");
    return 0;
}
