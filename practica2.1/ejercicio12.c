#include <time.h>
#include <stdio.h>
#include <errno.h>


int main() {

	time_t *aux;
	time_t t = time(aux);

	if (t == -1) {
		perror("Error_time");
	}
	else {
		printf("Segundos desde Epoch: %ld \n", t);
	}

    return 0;
}