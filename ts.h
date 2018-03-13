/*
Nic Q
Small library to make things easier.
2018/03/07
*/

#ifndef TS_H
#define TS_H

/* Pull in some libs */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* Define marcos */
#define chkopt(a)	(strcmp(argv[i], a) == 0)
#define dscopt(a,b)	(printf("\t%s\n\t\t%s\n", a, b))
#define debug(msg)	(fprintf(stderr, "DEBUG: %s\n", msg))


/* Prototypes */
void getts(char *);
time_t d2t(const char *);


#endif
