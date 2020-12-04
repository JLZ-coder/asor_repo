#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main() {

    umask(027);

    int fd;
    fd = open("prueba_7.txt", O_CREAT, 0777);

    if (fd == -1) {
        perror("Error_open");
        return 1;
    }

    return 0;
}