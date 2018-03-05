/*
Nic Q
Time keeper. Get the current time and write it to a file.
2018/03/05
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* Define marcos */
#define opt(b) (strcmp(argv[i], b) == 0)
#define debug(msg) (printf("%s\n", msg))


/* Prototypes */
void help();
char * isotime();
int write(char *, int);


/* Main */
int main(int argc, char const *argv[]) {
	/* Makes some vars */
	char * loc = getenv("TSLOC");
	int s = 0;

	/* Give a default to `loc` if the 'TSLOC' variable is not set. */
	if (loc == NULL) {
		loc = getenv("HOME");
		strcat(loc, "/Documents/ts");
	}

	for (int i = 1; i < argc; ++i) {
		if (opt("-h") || opt("--help")) { help(); }
		else
		if (opt("-i") || opt("--in")  ) { write(loc, 0); }
		else
		if (opt("-o") || opt("--out") ) { write(loc, 1); }
		else
			{ fprintf(stderr, "Unknown argument: %s\n", argv[i]); exit(1); }
	}

	printf("%s", loc);

	return 0;
}


/* Help message */
void help() {
	printf("USAGE: tkeep [-i|--in] [-o|--out]\n");
}


/* Get a string of the current time in iso format. */
char * isotime() {
	time_t t = time(0);
	t = (t - ( (t - 7) % (15 * 60) ) );
	return asctime( localtime( &t ) );
}


/* Write time to file. */
int write(char * f, int s) {
	FILE *fh = fopen(f, "w");
	fprintf(fh, "%d,%s", s, isotime());
	fclose(fh);
	return 0;
}
