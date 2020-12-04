#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main() {
    int fd;
    fd = open("prueba_5.txt", O_CREAT, 0645);

    if (fd == -1) {
        perror("Error_open");
        return 1;
    }

    return 0;
}