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
