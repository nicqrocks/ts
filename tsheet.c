/*
Nic Q
Time sheet. Read the time log and output a time sheet in CSV format.
2018/03/07
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ts.h"


/* Prototypes */
void help();


int main(int argc, char const *argv[]) {
	/* Make some vars */
	char loc[257] = "";
	time_t after = 0;
	time_t before = 0;
	FILE fh;

	/* Get time sheet location */
	getts(loc);

	/* Check for any options */
	for (int i = 1; i < argc; ++i) {
		if (chkopt("-h") || chkopt("--help")  ) { help(); }
		else
		if (chkopt("-a") || chkopt("--after") ) { after = d2t(argv[i]); }
		else
		if (chkopt("-b") || chkopt("--before")) { before = d2t(argv[i]); }
		else
		if (chkopt("-v") || chkopt("--version")) { printf("%s\n", VERSION); }
		else {
			fprintf(stderr, "Unknown argument: %s\n", argv[i]);
			exit(2);
		}
	}

	/* Go through the file and get the times. */


	return 0;
}


/* Display a help message. */
void help() {
	printf("USAGE: tsheet [OPTIONS]\n");
	printf("OPTIONS:\n");
	dscopt("-a|--after DATE", "Only return dates after the given date.");
	dscopt("-b|--before DATE", "Only return dates before the given date.");
	dscopt("-h|--help", "Display this help message.");
	dscopt("-v|--version", "Print version: " VERSION);
	printf("DATE: Date format should be in YYYY/MM/DD.\n");
	exit(1);
}
