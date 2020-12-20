#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <sys/types.h>


int main(int argc, char **argv) {

    if (argc < 2) {
        printf("ERROR: Hay que introducir un comando\n");
        return 1;
    }

    pid_t pid = fork();

    switch (pid) {
        case -1:
            perror("Error_fork");
            return 1;
            break;
        case 0:
            if (setsid() == -1) {
                perror("Error_setsid");
                return 1;
            }
            if (chdir("/tmp") == -1) {
                perror("Error_chdir");
                return 1;
            }
            
            int fd = open("/tmp/daemon.out", O_CREAT | O_RDWR, 0777);
            int fd1 = open("/tmp/daemon.err", O_CREAT | O_RDWR, 0777);
            int fd2 = open("/dev/null", O_CREAT | O_RDWR, 0777);

            dup2(fd, 1);
            dup2(fd1, 2);
            dup2(fd2, 0);

            int s;
            s = execvp(argv[1], &argv[1]);

            if (s == -1) {
                perror("Error_execvp");
                close(fd);
                close(fd1);
                close(fd2);
                return 1;
            }

            printf("Soy el hijo %i de %i\n", getpid(), getppid());

            close(fd);
            close(fd1);
            close(fd2);
            break;
        default:
            printf("Soy el padre %i\n", getpid());
    }

    return 0;
}