#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>


volatile int parado = 0;

void handler(int sig) {
    if (sig == SIGUSR1) {
        parado = 1;
    }
}

//No he usado sigsuspend, ya que aqui se necesita un temporizador para saber cuando borrar el ejecutable
//y usar la funcion suspenderia la cuenta atras hasta que se recibiera la señal SIGUSR1

int main(int argc, char **argv) {

    if (argc < 2 || argc > 2) {
        printf("ERROR: Hay que introducir un numero de segundos\n");
        return 1;
    }

    int secs = atoi(argv[1]);

    struct sigaction action;

    sigaction(SIGUSR1, NULL, &action);
    action.sa_handler = handler;
    sigaction(SIGUSR1, &action, NULL);

    int i = 0; 

    sigset_t signals;
    sigemptyset(&signals);

    while (i <= secs) {

        printf("Cuenta atras: %i\n", secs - i);

        if (parado == 1) {
            break;
        }

        i += 1;
        sleep(1);
    }

    printf("\n");

    if (parado == 0) {
        printf("Borrando el ejecutable... F\n");
        unlink(argv[0]);
    }
    else {
        printf("Salvado!!!\n");
    }

    return 0;
}