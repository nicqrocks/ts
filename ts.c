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
	if (tok == NULL) { err_ymd(d); }
	tparts.tm_year = strtol(tok, NULL, 10);

	tok = strtok(NULL, "/");
	if (tok == NULL) { err_ymd(d); }
	tparts.tm_mon = strtol(tok, NULL, 10);

	tok = strtok(NULL, "/");
	if (tok == NULL) { err_ymd(d); }
	tparts.tm_mday = strtol(tok, NULL, 10);

	tm_norm(&tparts);
	out = mktime(&tparts);
	return out;
}


/*
Alter the values of a `tm` struct so that the values match what the struct
actually expects.
*/
void tm_norm(struct tm * dt) {
	dt->tm_year -= 1900;
	dt->tm_mon  -= 1;
}


/* Error out due to date formatting problems. */
void err_ymd(const char * msg) {
	err("Date format must be YYYY/MM/DD");
	if (msg != NULL) { fprintf(stderr, "\tGot: %s\n", msg); }
	exit(11);
}


/* Free the memory for each item in the linked list. */
void freell(struct Time * node) {
	if (node != NULL) {
		freell(node->next);
		free(node);
	}
}
