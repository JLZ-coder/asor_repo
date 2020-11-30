#include <unistd.h>
#include <stdio.h>
#include <errno.h>


int main() {

    long num;

    errno = 0;

    num = pathconf("/", _PC_LINK_MAX);
    if (num == -1 && errno > 0) {
        perror("Error_pathconfig");
        return 0;
    }
    else {
        printf("Enlaces maximos : %ld\n", num);
    }

    num = pathconf("/", _PC_PATH_MAX);
    if (num == -1 && errno > 0) {
        perror("Error_pathconfig");
        return 0;
    }
    else {
        printf("Maxima longitud ruta : %ld\n", num);
    }

    num = pathconf("/", _PC_NAME_MAX);
    if (num == -1 && errno > 0) {
        perror("Error_pathconfig");
        return 0;
    }
    else {
        printf("Longitud de titulo maxima : %ld\n", num);
    }

    return 1;
}