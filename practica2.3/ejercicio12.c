#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

volatile int ctr_SIGINT = 0;
volatile int ctr_SIGTSTP = 0;
volatile int ctr = 0;

void handler(int sig) {
    if (sig == SIGINT) {
        ctr_SIGINT += 1;
    }
    if (sig == SIGTSTP) {
        ctr_SIGTSTP += 1;
    }
    ctr += 1;
}

int main(int argc, char **argv) {

    struct sigaction action;

    sigaction(SIGINT, NULL, &action);
    action.sa_handler = handler;
    sigaction(SIGINT, &action, NULL); 

    sigaction(SIGTSTP, NULL, &action);
    action.sa_handler = handler;
    sigaction(SIGTSTP, &action, NULL); 


    sigset_t signals;
    sigemptyset(&signals);

    while (1) {

        sigsuspend(&signals);

        if (ctr >= 10) {
            break;
        }

    }

    printf("\n");
    printf("Señales de Interrupcion: %i\n", ctr_SIGINT);
    printf("Señales de Stop: %i\n", ctr_SIGTSTP);

    return 0;
}