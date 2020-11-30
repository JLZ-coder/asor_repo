#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


int main() {

    printf("Usuario real: %d \n", getuid());
    printf("Usuario efectivo: %d \n", geteuid());

    //Podemos asegurar que setuid esta activado en este fichero cuando
    //getuid y geteuid son diferentes.

    return 0;
}