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
    

    if (bind(sfd, rp->ai_addr, rp->ai_addrlen) != 0) {
        close(sfd);
        fprintf(stderr, "Could not bind\n");
        return 1;
    }

    freeaddrinfo(result);


    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(addr);
    char buf[2];
    char host[NI_MAXHOST], service[NI_MAXSERV];
    ssize_t nread;

    while(1) {
        nread = recvfrom(sfd, buf, 2, 0,
                (struct sockaddr *) &addr, &addr_len);
        buf[1] = '\0';

        s = getnameinfo((struct sockaddr *) &addr,
                            addr_len, host, NI_MAXHOST,
                            service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        if (s == 0)
            printf("%ld bytes de %s:%s\n",
                    (long) nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

        struct tm *t;
        time_t aux = time(NULL);
        t = localtime(&aux);
        size_t size;

        char c[50];

        switch(buf[0]) {
            case 't':
                size = strftime(c, 50, "%I:%M:%S %p", t);
                c[size] = '\0';
                
                sendto(sfd, c, size + 1, 0, (struct sockaddr *) &addr, addr_len)
                
                break;
            case 'd':
                size = strftime(c, 50, "%Y-%m-%d", t);
                c[size] = '\0';
                
                sendto(sfd, c, size + 1, 0, (struct sockaddr *) &addr, addr_len)

                break;
            case 'q':
                printf("Saliendo...\n");
                close(sfd);
                return 0;
                break;
            default:
                printf("Comando no soportado %s\n", buf);
        }
    }
    
    close(sfd);
    return 0;
}