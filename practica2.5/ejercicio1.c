#include <sys/socket.h> 
#include <netdb.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char **argv) {

    if (argc < 2 || argc > 2) {
        printf("ERROR: Hay que introducir solo un argumento\n");
        return 1;
    }

    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int s = getaddrinfo(argv[1], NULL, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }


    for (rp = result; rp != NULL; rp = rp->ai_next) {

        char host[NI_MAXHOST], service[NI_MAXSERV];

        int s = getnameinfo(rp->ai_addr,
                        rp->ai_addrlen, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICHOST);

       if (s == 0) {
            printf("%s\t", host);
            printf("%i\t",rp->ai_family);
            printf("%i\n", rp->ai_socktype);
       }
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
    }

    freeaddrinfo(result);

    return 0;
}