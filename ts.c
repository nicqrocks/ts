/*
Nic Q
Small library to make things easier.
2018/03/07
*/

#include "ts.h"


/* Get the location of the timesheet file */
void getts(char * str) {
	char * tmp;
	int len = 0;
	int i = 0;

	tmp = getenv("TSLOC");
	if (tmp == NULL) {
		tmp = getenv("HOME");
		strcat(tmp, "/Documents/ts");
	}

	while (tmp[i] != '\0') {
		str[i] = tmp[i];
		++i;
	}

	str[i] = '\0';
}


/* Convert date string in "yyyy/mm/dd" to a time_t. */
time_t d2t(const char * d) {
	struct tm tparts = {};
	time_t out = 0;
	char date[257] = "";
	char * tok;

	strcpy(date, d);

	tok = strtok(date, "/");
	tparts.tm_year = strtol(tok, NULL, 10) - 1900;

	tok = strtok(NULL, "/");
	tparts.tm_mon = strtol(tok, NULL, 10) - 1;

	tok = strtok(NULL, "/");
	tparts.tm_mday = strtol(tok, NULL, 10);

	out = mktime(&tparts);
	return out;
}

