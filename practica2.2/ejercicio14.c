#include <time.h>
#include <stdio.h>
#include <errno.h>


int main() {

	struct tm *t;
	time_t aux = time(NULL);

	t = localtime(&aux);

	if (t == NULL) {
		perror("Error_localtime");
		return 1;
	}

	printf("Anio: %i\n", t->tm_year + 1900);

    return 0;
}