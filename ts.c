/*
Nic Q
Small library to make things easier.
2018/03/07
*/

#include "ts.h"

/* Get the location of the timesheet file */
void getts(char * str) {
	char * tmp;
	tmp = getenv("TSLOC");
	if (tmp == NULL) {
		tmp = getenv("HOME");
		strcat(tmp, "/Documents/ts");
	}
	for (int i = 0; tmp[i] != '\0'; ++i) {
		str[i] = tmp[i];
	}
}
