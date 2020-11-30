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

	char c[50];

	strftime(c, 50, "%A, %d de %B de %Y, %R", t);

	printf("%s\n", c);

    return 0;
}