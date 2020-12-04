#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <stdlib.h>


int main(int argc, char **argv) {

    if (argc > 2 || argc < 2) {
    	printf("ERROR: Hay que introducir un solo fichero\n");
    	return 1;
    }

    int s;
    struct stat buf;

    s = stat(argv[1], &buf);

    if (s == -1) {
        perror("Error_stat");
        return 1;
    }


    //Major y minor
    printf("Major y Minor: %i , %i\n", major(buf.st_dev), minor(buf.st_dev));


    //I-nodo
    printf("I-nodo: %li\n", buf.st_ino);


    //Tipo de fichero
    printf("Tipo de fichero: ");

    switch (buf.st_mode & S_IFMT) {
	    case S_IFDIR:  printf("Directorio\n");               break;
	    case S_IFLNK:  printf("Enlace simbolico\n");                 break;
	    case S_IFREG:  printf("Fichero regular\n");            break;
	    default:       printf("unknown?\n");                break;
    }

    //Ultimo acceso
	printf("Ultimo acceso: %s\n", ctime(&buf.st_atime));

    //mtime se actualiza cuando se modifica el contenido del archivo o cuando es creado
    //ctime se actualiza cuando el archivo cambia de permisos, de propietario, de numero de links,etc

    return 0;
}