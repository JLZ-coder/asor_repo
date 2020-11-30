#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>


int main() {

    long num;

    errno = 0;

    num = sysconf(_SC_ARG_MAX);
    if (num == -1 && errno > 0) {
        perror("Error_sysconfig");
        return 0;
    }
    else {
        printf("Argumentos maximos : %ld\n", num);
    }

    num = sysconf(_SC_CHILD_MAX);
    if (num == -1 && errno > 0) {
        perror("Error_sysconfig");
        return 0;
    }
    else {
        printf("Numero maximo de hijos : %ld\n", num);
    }

    num = sysconf(_SC_OPEN_MAX);
    if (num == -1 && errno > 0) {
        perror("Error_sysconfig");
        return 0;
    }
    else {
        printf("Numero maximo de ficheros por proceso : %ld\n", num);
    }

    return 1;
}