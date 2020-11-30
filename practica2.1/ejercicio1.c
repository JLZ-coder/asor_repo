#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {

   if (setuid(0) == -1) {
       perror("Error_setuid");
   }

   return 0;
}
