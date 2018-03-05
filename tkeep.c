/*
Nic Q
Time keeper. Get the current time and write it to a file.
2018/03/05
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* Main */
int main(int argc, char const *argv[]) {
	/* Makes some vars */
	char * loc = getenv("TSLOC");
	time_t t = time(0);

	/* Give a default to `loc` if the 'TSLOC' variable is not set. */
	if (loc == NULL) {
		loc = getenv("HOME");
		strcat(loc, "/Documents/ts");
	}

	for (int i = 0; i < argc; ++i) {
		/**/
	}

	printf("%s", loc);

	return 0;
}
