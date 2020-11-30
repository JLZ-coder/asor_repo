#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {

    int i;

    for (i = 1; i < 256; i++) {
        printf("%d : %s \n", i, strerror(i));
    }

   return 0;
}
