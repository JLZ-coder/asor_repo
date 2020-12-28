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

    if (argc != 3) {
        printf("ERROR: Solo hay que introducir direccion y puerto\n");
        return 1;
    }

    struct addrinfo hints;
    struct addrinfo *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Stream socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int s = getaddrinfo(argv[1], argv[2], &hints, &rp);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    int sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1) {
        perror("Error_socket");
        return 1;
    }
    
    if (bind(sfd, rp->ai_addr, rp->ai_addrlen) != 0) {
        close(sfd);
        fprintf(stderr, "Could not bind\n");
        return 1;
    }

    freeaddrinfo(rp);

    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(addr);

    char buf[256];
    char host[NI_MAXHOST], service[NI_MAXSERV];
    ssize_t nread;

    listen(sfd, 3);

    int sd;
    s = 0;

    while(1) {
        sd = accept(sfd,(struct sockaddr *) &addr, &addr_len);

        s = getnameinfo((struct sockaddr *) &addr,
                        addr_len, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

        printf("Conexion desde %s:%s\n", host, service);

        while (nread = recv(sd, buf, 256, 0)) { // Comprobar mensaje!
            if (nread == 2 && buf[0] == 'Q') {
                printf("Conexion terminada\n");
                close(sd);
                close(sfd);
                return 0;
            }
            buf[nread] = '\0';
            send(sd, buf, nread, 0);
        }
        printf("Conexion terminada\n");
    }
    
    close(sfd);
    close(sd);
    return 0;
}