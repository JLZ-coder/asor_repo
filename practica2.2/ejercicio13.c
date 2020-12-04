#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>


int main() {

	struct timeval start, end;
	struct timezone aux;

	int i;

	if (gettimeofday(&start, &aux) == -1) {
		perror("Error_gettimeofday");
		return 1;
	}

	for (i = 0; i < 1000000; i++) {}

	if (gettimeofday(&end, &aux) == -1) {
		perror("Error_gettimeofday");
		return 1;
	}

	long dif = end.tv_usec - start.tv_usec;

	printf("Lo que ha tardado la funcion: %ld\n", dif);

    return 0;
}