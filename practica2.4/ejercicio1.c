#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>


int main(int argc, char **argv) {

    if (argc < 4) {
        printf("ERROR: Hay que introducir los comandos\n");
        return 1;
    }

    int fd[2];
    if (pipe(fd) == -1) {
        perror("Error_pipe");
        return 1;
    }

    pid_t pid = fork();

    switch (pid) {
        case -1:
            perror("Error_fork");
            return 1;
            break;
        case 0:
            dup2(fd[0], 0);

            close(fd[0]);
            close(fd[1]);

            execlp(argv[3], argv[3], argv[4], NULL);

            break;
        default:
            dup2(fd[1], 1);

            close(fd[0]);
            close(fd[1]);

            execlp(argv[1], argv[1], argv[2], NULL);
    }

    return 0;
}