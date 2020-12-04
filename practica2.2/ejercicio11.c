#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


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

    if (S_ISREG(buf.st_mode)) { 
    	char hard[strlen(argv[1]) + 6];
    	char sim[strlen(argv[1]) + 5];

    	strcpy(hard, argv[1]);
    	strcpy(sim, argv[1]);
    	strcat(hard, ".hard");
    	strcat(sim, ".sym");
    	if (link(argv[1], hard) == -1) {
	        perror("Error_link");
	        return 1;
    	}

    	if (symlink(argv[1], sim) == -1) {
	        perror("Error_symlink");
	        return 1;
    	}
    }

    return 0;
}