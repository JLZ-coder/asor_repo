#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {

    if (argc < 2) {
        printf("ERROR: Hay que introducir un comando\n");
        return 1;
    }

    int len = 0;
    int i;

    for (i = 1; i < argc; i++) {
        len += strlen(argv[i]) + 1;
    }

    len += 1;

    char *command = malloc(sizeof(char) * len);

    for (i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    int s;
    s = system(command);

    if (s == -1) {
        perror("Error_system");
        return 1;
    }

    free(command);

    printf("El comando terminó de ejecutarse.\n");

    //La cadena se imprime una vez terminado el comando que se ha pasado a system. System crea
    //un proceso hijo para ejecutar el comando, una vez termina en proceso padre sigue con la
    //ejecucion.

    return 0;
}