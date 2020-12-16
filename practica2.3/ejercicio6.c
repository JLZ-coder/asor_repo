#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(int argc, char **argv) {

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
            //sleep(5);
            printf("Soy el hijo %i de %i\n", getpid(), getppid());
            break;
        default:
            printf("Soy el padre %i\n", getpid());
    }

    //Si el padre termina antes, el hijo se queda huerfano y es adoptado por el proceso 1
    //Si el hijo termina antes pasa a ser zombi, aun esta en la tabla de procesos pero ya ha 
    //terminado su ejecución.

    return 0;
}