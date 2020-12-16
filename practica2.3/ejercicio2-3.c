#include <sched.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv) {

	int pol;
    pol = sched_getscheduler(0);

    if (pol == -1) {
        perror("Error_getsched");
        return 1;
    }

    int priori_max = sched_get_priority_max(pol);
    int priori_min = sched_get_priority_min(pol);

    switch (pol) {
        case SCHED_OTHER:
            printf("Politica OTHER");
            break;
        case SCHED_FIFO:
            printf("Politica FIFO");
            break;
        case SCHED_RR:
            printf("Politica RR");
            break;
        default:
            printf("Politica Especial");
    }

    printf(" (%s, %s) : ", priori_min, priori_max);

    struct sched_param param;
    sched_getparam(0,&param);

   	printf("Prioridad de %i\n", param.sched_priority);

    //Respondiendo al ejercicio3, si que se heredan los atributos de planificacion

    return 0;
}