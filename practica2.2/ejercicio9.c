#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
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

    s = lstat(argv[1], &buf);

    if (s == -1) {
        perror("Error_stat");
        return 1;
    }

    printf("Major y Minor: %i , %i\n", major(buf.st_dev), minor(buf.st_dev));


    printf("I-nodo: %li\n", buf.st_ino);


    printf("Tipo de fichero: ");

    if (S_ISDIR(buf.st_mode)) {
        printf("Directorio\n");
    }
    else if (S_ISLNK(buf.st_mode)) {
        printf("Enlace simbolico\n"); 
    }
    else if (S_ISREG(buf.st_mode)) {
        printf("Fichero regular\n"); 
    }
    else {
        printf("unknown?\n");
    }

	printf("Ultimo acceso: %s\n", ctime(&buf.st_atime));

    return 0;
}