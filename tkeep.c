/*
Nic Q
Time keeper. Get the current time and write it to a file.
2018/03/05
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ts.h"


/* Prototypes */
void help();
char * isotime(char *);
int write(char *, int);


/* Main */
int main(int argc, char const *argv[]) {
	/* Makes some vars */
	char loc[257];
	int s = 0;

	/* Get the location of the timesheet */
	getts(loc);

	/* Display help if no arguments were given. */
	if (argc == 1) { help(); }

	/* Go through the arguments given. */
	for (int i = 1; i < argc; ++i) {
		if (chkopt("-h") || chkopt("--help")) { help(); }
		else
		if (chkopt("-i") || chkopt("--in")  ) { write(loc, 0); }
		else
		if (chkopt("-o") || chkopt("--out") ) { write(loc, 1); }
		else
		if (chkopt("-v") || chkopt("--version")) { printf("%s\n", VERSION); }
		else {
			fprintf(stderr, "Unknown argument: %s\n", argv[i]);
			exit(2);
		}
	}

	return 0;
}


/* Help message */
void help() {
	printf("USAGE: tkeep [OPTIONS]\n");
	printf("OPTIONS:\n");
	dscopt("-h|--help", "Print help options");
	dscopt("-i|--in", "Record IN time");
	dscopt("-o|--out", "Record OUT time");
	dscopt("-v|--version", "Print version: " VERSION);
	exit(1);
}


/* Get a string of the current time in iso format. */
char * isotime(char * str) {
	time_t t = time(0);
	t += 420;
	t = (t - ( t % (15 * 60) ) );
	strftime(str, 64, "%FT%T%z", localtime(&t));
	return str;
}


/* Write time to file. */
int write(char * f, int s) {
	char iso[64];
	FILE *fh = fopen(f, "a");

	if (fh == NULL) {
		fprintf(stderr, "Can not write to '%s'\n", f);
		return 0;
	}

	isotime(iso);
	fprintf(fh, "%d,%s\n", s, iso);

	fclose(fh);
	return 1;
}
