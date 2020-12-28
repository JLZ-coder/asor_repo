#include <sys/socket.h> 
#include <netdb.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {

    if (argc != 4) {
        printf("ERROR: Solo hay que introducir direccion, puerto y caracter a enviar\n");
        return 1;
    }

    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

        int s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    rp = result;

    int sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1) {
        perror("Error_socket");
        return 1;
    }

    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(addr);
    char buf[50];
    char host[NI_MAXHOST], service[NI_MAXSERV];
    ssize_t nread;

    sendto(sfd, argv[3], 2, 0, rp->ai_addr, rp->ai_addrlen);

    if (*argv[3] == 't' || *argv[3] == 'd') {
        nread = recvfrom(sfd, buf, 50, 0,
                (struct sockaddr *) &addr, &addr_len);
        buf[nread] = '\0';

        printf("%s\n", buf);
    }

    freeaddrinfo(result);
    
    close(sfd);
    return 0;
}