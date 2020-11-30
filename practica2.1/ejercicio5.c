#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main() {

    struct utsname buf;

    if (uname(&buf) == -1) {
    	perror("Error_uname");
    }
    else {
        printf("%s\n", buf.sysname);
        printf("%s\n", buf.nodename);
        printf("%s\n", buf.release);
        printf("%s\n", buf.version);
        printf("%s\n", buf.machine);
    }
    
   return 0;
}