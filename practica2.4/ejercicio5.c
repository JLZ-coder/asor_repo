#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv) {

    printf("Los archivos FIFO se llaman 'tuberia5'y 'prueba_ej3'.\n");

    char nombre[9];
    strcpy(nombre, "tuberia5");
    char nombre1[11];
    strcpy(nombre1, "prueba_ej3");

    //mkfifo(nombre, 0777);
    //mkfifo(nombre1, 0777);

    int fd = open(nombre, O_RDONLY | O_NONBLOCK);
    int fd1 = open(nombre1, O_RDONLY | O_NONBLOCK);

    char nom_actual[11];
    int fd_actual = -1;

    ssize_t size = 256;

    char buff[256];
    
    int max = (fd < fd1)? fd1 + 1 : fd + 1;

    int cambios = 0;

    while (cambios != -1) {


        fd_set set;
        FD_ZERO(&set);
        FD_SET(fd, &set);
        FD_SET(fd1, &set);
        cambios = select(max, &set, NULL, NULL, NULL);


        if (cambios > 0) {

            if (FD_ISSET(fd, &set)) {
                fd_actual = fd;
                strcpy(nom_actual, nombre);
            }
            else if (FD_ISSET(fd1, &set)) {
                fd_actual = fd1;
                strcpy(nom_actual, nombre1);
            }


            size = read(fd_actual, buff, 256);
            buff[size] = '\0';
            if (size > 0) {
                printf("Proveniente de %s: %s \n", nom_actual, buff);
            }


            if (size == 0) {
                if (fd_actual == fd) {
                    close(fd);
                    fd = open(nombre, O_RDONLY | O_NONBLOCK);
                }
                else if (fd_actual == fd1) {
                    close(fd1);
                    fd1 = open(nombre1, O_RDONLY | O_NONBLOCK);
                }
            }
        }
    }

    close(fd);
    close(fd1);

    return 0;
}