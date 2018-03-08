/*
Testing the `ts` library.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ts.h"

/* Define some macros. */
#define plan(a) ( printf("1..%d\n", a) )
#define ok(a) ( printf("ok %d - %s\n", ++TAP_COUNT, a) )
#define nok(a) ( printf("not ok %d - %s\n", ++TAP_COUNT, a) )
#define donet() ( printf("1..%d\n", TAP_COUNT) )


/* Global to keep track of test numbers. */
int TAP_COUNT = 0;


/* Prototypes */
int chkgetts(char *, char *);


int main() {
	char * home = getenv("HOME");

	strcat(home, "/Documents/ts");
	chkgetts("ts", "ts");
	chkgetts(NULL, home);

	donet();

	return 0;
}


/* Check if the getts function works. */
int chkgetts(char * ev, char * ex) {
	char ts[257];
	
	if (ev != NULL) {
		setenv("TSLOC", ev, 1);
	} else {
		unsetenv("TSLOC");
	}
	
	getts(ts);
	
	if (strcmp(ts, ex) == 0) {
		ok("`getts` gives the correct location");
	} else {
		char tmp[257];
		strcat(tmp, "Got ");
		strcat(tmp, ts);
		strcat(tmp, " and expected ");
		strcat(tmp, ex);
		nok(tmp);
	}
	return 1;
}
