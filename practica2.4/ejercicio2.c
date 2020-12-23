#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv) {

    int h_p[2];
    int p_h[2];

    if (pipe(h_p) == -1 || pipe(p_h) == -1) {
        perror("Error_pipe");
        return 1;
    }

    pid_t pid = fork();

    switch (pid) {
        case -1:
            perror("Error_fork");
            return 1;
            break;
        case 0:
            close(p_h[1]);
            close(h_p[0]);

            char buf_h[100];
            char buf2_h[1] = {'l'};
            int i;

            for (i = 0; i < 10; i++) {
                ssize_t size = read(p_h[0], buf_h, 99);
                buf_h[size] = '\0';
                printf("HIJO (mensaje %i): %s\n", i + 1, buf_h);

                sleep(1);

                if (i == 9) {
                    buf2_h[0] = 'q';
                }

                write(h_p[1], buf2_h, 1);
            }

            close(p_h[0]);
            close(h_p[1]);
            break;
        default:
            close(p_h[0]);
            close(h_p[1]);

            char buf[100];
            char buf2[1] = {' '};

            do {
                //printf("PADRE: ");
                ssize_t size = read(0, buf, 99);
                buf[size] = '\0';
                write(p_h[1], buf, size + 1);

                read(h_p[0], buf2, 1);
                

            } while (buf2[0] != 'q');


            close(p_h[1]);
            close(h_p[0]);
    }

    return 0;
}