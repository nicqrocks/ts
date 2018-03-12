/*
Testing the `ts` library.
*/

#define _XOPEN_SOURCE 600

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
int chk_getts(char *, char *);
int chk_d2t(char *);


int main() {
	char * home = getenv("HOME");
	strcat(home, "/Documents/ts");

	chk_getts("ts", "ts");
	chk_getts(NULL, home);

	chk_d2t("2018/03/06");
	chk_d2t("2018/03/07");
	chk_d2t("2018/03/12");

	donet();

	return 0;
}


/* Check if the getts function works. */
int chk_getts(char * ev, char * ex) {
	char ts[257];

	if (ev != NULL) {
		setenv("TSLOC", ev, 1);
	} else {
		unsetenv("TSLOC");
	}

	getts(ts);

	if (strcmp(ts, ex) == 0) {
		ok("`getts` gives the correct location");
		return 1;
	} else {
		char tmp[257] = "";
		sprintf(tmp, "Got '%s' and expected '%s'\n", ts, ex);
		nok(tmp);
		return 0;
	}
}


/* Check if `d2t` can convert from a date string to time_t. */
int chk_d2t(char * d) {
	time_t r = d2t(d);
	struct tm * tmp = localtime(&r);
	char * rd;

	strftime(rd, 12, "%Y/%m/%d", tmp);

	if (strcmp(rd, d) == 0) {
		ok("`d2t` gives the correct time_t");
		return 0;
	} else {
		char tmp[257];
		sprintf(tmp, "`d2t` gave %s instead of %s");
		nok(tmp);
		return 1;
	}
}
