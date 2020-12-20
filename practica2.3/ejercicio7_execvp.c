#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv) {

    if (argc < 2) {
        printf("ERROR: Hay que introducir un comando\n");
        return 1;
    }


    int s;
    s = execvp(argv[1], &argv[1]);

    if (s == -1) {
        perror("Error_execvp");
        return 1;
    }

    printf("El comando terminó de ejecutarse.\n");

    //Aqui no se ejecuta el printf del ultimo mensaje. En este caso se reemplaza el proceso por 
    //uno nuevo, el que le digamos por los argumentos.

    return 0;
}