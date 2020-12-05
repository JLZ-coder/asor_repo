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
    fd = open(argv[1], O_CREAT | O_RDWR, 0666);

    if (fd == -1) {
        perror("Error_open");
        return 1;
    }

    if (dup2(fd, 1) == -1) {
        perror("Error_dup2");
        return 1;
    }

    if (dup2(1, 2) == -1) {
        perror("Error_dup2");
        return 1;
    }

    printf("Probando, probando... en salida estandar\n");

   	fprintf(stderr, "Probando en salida de error\n");

    close(fd);

    //ls > dirlist 2>&1, esto redirecciona la salida estandar a dirlist y luego redirecciona la salida
    //de error a la salida estandar, la cual ya estaba apuntando a dirlist

    //ls 2>&1 > dirlist, redirecciona la salida de error a la salida estandar, la cual 
    //escribe en terminal, por lo que la salida de error tambien escribira en terminal.
    //Si luego redirigimos la salida estandar a dirlist, la salida de error sigue apuntando
    //a la terminal


    return 0;
}
