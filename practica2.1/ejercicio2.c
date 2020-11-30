#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {

   if (setuid(0) == -1) {
       printf("%d : %s \n", errno, strerror(errno));
   }

   return 1;
}
