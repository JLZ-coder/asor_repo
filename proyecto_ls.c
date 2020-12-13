#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int main(int argc, char **argv) {

	if (argc > 2 || argc < 2) {
    	printf("ERROR: Hay que introducir un solo directorio\n");
    	return 1;
    }

    DIR *dir;
    dir = opendir(argv[1]);

    if (dir == NULL) {
    	perror("Error_opendir");
        return 1;
    }

    struct dirent *actual;
    actual = readdir(dir);

    int total = 0;
    int bufsiz;
    int nbytes;

    while (actual != NULL) {
    	char *long_ruta = malloc( sizeof(char) * (strlen(argv[1]) + strlen(actual->d_name) + 1) );

    	strcpy(long_ruta, argv[1]);
    	strcat(long_ruta, "/");
    	strcat(long_ruta, actual->d_name);

    	int s;
	    struct stat buf;

	    s = lstat(long_ruta, &buf);

	    if (s == -1) {
	        perror("Error_stat");
	        free(long_ruta);
	        closedir(dir);
	        return 1;
	    }

	    if (S_ISDIR(buf.st_mode)) {
	    	printf("%s/\n", actual->d_name);  
	    }
	    else if (S_ISLNK(buf.st_mode)) {
	    	bufsiz = buf.st_size + 1;

	    	if (buf.st_size == 0)
            	bufsiz = PATH_MAX;

        	char *link = malloc(bufsiz);

	        nbytes = readlink(long_ruta, link, bufsiz);
	        if (nbytes == -1) {
	            perror("Error_readlink");
	            free(long_ruta);
		        closedir(dir);
		        return 1;
	        }

	    	printf("%s->%s\n", actual->d_name, link);

	    	free(link);   

	    	total = total + ((buf.st_blksize/8)*buf.st_blocks); 
	    }
	    else if (buf.st_mode & S_IXUSR) {
	    	printf("%s*\n", actual->d_name);

	    	total = total + ((buf.st_blksize/8)*buf.st_blocks);  
	    }
	    else if (S_ISREG(buf.st_mode)) {
	    	printf("%s\n", actual->d_name);  

	    	total = total + ((buf.st_blksize/8)*buf.st_blocks);   
	    }
	    else {
	    	printf("unknown?\n");   
	    }

    	actual = readdir(dir);
    	free(long_ruta);

    }

    printf("Tamanio de ficheros (kB): %d\n", total);

    
    closedir(dir);

    return 0;
}