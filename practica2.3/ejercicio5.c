#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(int argc, char **argv) {

    int pid;
    pid = getpid();

    printf("PID: %i\n", pid);
    printf("ParentPID: %i\n", getppid());

    printf("GroupPID: %i\n", getpgid(0));
    printf("SessionPID: %i\n", getsid(0));

    struct rlimit limit;

    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("Error_getrlimit");
        return -1;
    }

    printf("Limite de ficheros: %li\n", limit.rlim_max);

    char *buf = malloc(sizeof(char) * 1000);

    if (getcwd(buf, 1000) == NULL) {
        perror("Error_getcwd");
        return 1;
    }

    printf("En el Directorio: %s\n", buf);

    return 0;
}