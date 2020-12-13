#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>


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

    struct flock info;

    info.l_type = F_WRLCK;
    info.l_whence = SEEK_SET;
    info.l_start = 0;
    info.l_len = 0;
    info.l_pid = getpid();

    fcntl(fd, F_GETLK, &info);

    if (info.l_type == F_UNLCK) {
    	printf("Fichero desbloqueado\n");

    	info.l_type = F_WRLCK;
	    info.l_whence = SEEK_SET;
	    info.l_start = 0;
	    info.l_len = 0;

	   	if (fcntl(fd, F_SETLK, &info) == -1) {
	   		perror("Error_fcntl_setlock");
	   		close(fd);
	   		return 1;
	   	}
	   	printf("Aplicando cerrojo\n");

    	struct tm *t;
		time_t aux = time(NULL);

		t = localtime(&aux);

		if (t == NULL) {
			perror("Error_localtime");
			close(fd);
			return 1;
		}

		char c[50];

		strftime(c, 50, "%T\n", t);

		printf("%s", c);

		write(fd, &c, strlen(c));

		sleep(30);

		info.l_type = F_UNLCK;
	    info.l_whence = SEEK_SET;
	    info.l_start = 0;
	    info.l_len = 0;

	    if (fcntl(fd, F_SETLK, &info) == -1) {
	   		perror("Error_fcntl_setlock");
	   		close(fd);
	   		return 1;
	   	}
	   	printf("Quitando cerrojo\n");
    }
    else {
    	printf("Fichero bloqueado\n");
    }

    close(fd);

    return 0;
}