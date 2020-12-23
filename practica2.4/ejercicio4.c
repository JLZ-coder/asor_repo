#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv) {

    printf("El archivo FIFO se llama 'prueba_ej3'.\n");

    if (argc < 2) {
        printf("ERROR: Hay que introducir un parametro al menos\n");
        return 1;
    }

    char nombre[11];
    strcpy(nombre, "prueba_ej3");

    //mkfifo(nombre, 0777);

    int fd = open(nombre, O_WRONLY);
    strcat(argv[1], "\n");

    write(fd, argv[1], strlen(argv[1]));

    close(fd);

    return 0;
}