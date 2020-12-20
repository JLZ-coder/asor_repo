#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

    sigset_t signals;

    sigemptyset(&signals);
    sigaddset(&signals, SIGINT);
    sigaddset(&signals, SIGTSTP);

    sigprocmask(SIG_BLOCK, &signals, NULL);

    //kill(getpid(),SIGTSTP);

    char *sleep_sec = getenv("SLEEP_SECS");

    if (sleep_sec == NULL) {
        sleep_sec = "10";
    }
    int segs = atoi(sleep_sec);

    sleep(segs);


    sigset_t waiting;
    sigpending(&waiting);

    if (sigismember(&waiting, SIGINT) == 1) {
        printf("Se recibio la señal SIGINT.\n");
    }
    else {
        printf("No se recibio la señal SIGINT.\n");
        sigdelset(&signals, SIGINT);
    }

    if (sigismember(&waiting, SIGTSTP) == 1) {
        printf("Se recibio la señal SIGSTP.\n");
    }
    else {
        printf("No se recibio la señal SIGSTP.\n");
        sigdelset(&signals, SIGTSTP);
    }

    sigprocmask(SIG_UNBLOCK, &signals, NULL);

    printf("El proceso se ha terminado.\n");

    return 0;
}