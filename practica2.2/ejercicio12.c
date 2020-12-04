#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {

	if (argc > 2 || argc < 2) {
    	printf("ERROR: Hay que introducir un solo fichero\n");
    	return 1;
    }

	int fd;
    fd = open(argv[1], O_CREAT || O_RDWR, 0777);

    if (fd == -1) {
        perror("Error_open");
        return 1;
    }

    if (dup2(fd, 1) == -1) {
        perror("Error_dup2");
        return 1;
    }

    printf("Probando, probando...\n");

    close(fd);

    return 0;
}