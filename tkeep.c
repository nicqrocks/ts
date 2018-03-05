/*
Nic Q
Time keeper. Get the current time and write it to a file.
2018/03/05
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* Prototypes */
char * cat(char *, char *);
int cmps(char *, char *);


/* Main */
int main(int argc, char const *argv[]) {
	/* Makes some vars */
	char * loc = getenv("TSLOC");
	time_t t = time(0);

	/* Give a default to `loc` if the 'TSLOC' variable is not set. */
	if (loc == NULL) {
		loc = getenv("HOME");
		cat(loc, "/Documents/ts");
	}

	printf("%s", loc);

	return 0;
}


/* Bring two strings together. */
char * cat(char * d, char * s) {
	/* Make some vars. */
	size_t len = 0, i = 0;
	/* Find the end of the destination string. */
	while (d[len] != '\0') { ++len; }
	/* Add the `s` string to the `d` string. */
	for (i = 0; s[i] != '\0'; ++i) { d[len + i] = s[i]; }
	d[len + i] = '\0';
	return d;
}


/* Compare two strings. */
int cmps(char * a, char * b) { }
