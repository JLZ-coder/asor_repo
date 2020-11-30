#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>


int main() {

    printf("Usuario real: %d \n", getuid());
    printf("Usuario efectivo: %d \n", geteuid());

    struct passwd *info;

    info = getpwuid(getuid());

    printf("Nombre: %s \n", info->pw_name);
    printf("HOME: %s \n", info->pw_dir);
    printf("Descripcion: %s \n", info->pw_gecos);

    return 1;
}