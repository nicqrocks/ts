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

/* Define macros */
#define strdate(s, tm) (sprintf(s, "%04d/%02d/%02d", tm.tm_year, tm.tm_mon, tm.tm_mday))
#define strtime(s, tm) (sprintf(s, "%02d:%02d", tm.tm_hour, tm.tm_min))


/* Prototypes */
void help();
int parse_line(FILE *, int *, struct tm *);
struct Time * find_date(struct Time *, char *);
struct Time * get_last(struct Time *);


int main(int argc, char const *argv[]) {
	/* Make some vars */
	struct Time * tbase = NULL;
	struct Time * last = NULL;
	struct Time * node = NULL;
	struct tm dt = {};
	time_t after = 0;
	time_t before = 0;
	char fn[257] = "";
	FILE * fh;
	int fcheck = 0;
	int state = 0;

	/* Get time sheet location */
	getts(fn);

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

	/* Open the file. */
	fh = fopen(fn, "r");
	if (fh == NULL) {
		fprintf(stderr, "Failed to open '%s'", fn);
		exit(2);
	}

	/* Read through the file and grab dates. */
	fcheck = parse_line(fh, &state, &dt);
	while (fcheck != -1) {
		/* Make some vars. */
		char ymd[12] = "";

		/* Check if this date is before or after the  */
		if (before != 0 && mktime(&dt) < before) { continue; }
		if (after  != 0 && mktime(&dt) > after ) { continue; }

		/* Determine the point in the linked list to add this item. */
		strdate(ymd, dt);
		if (tbase == NULL) {
			tbase = malloc( sizeof( struct Time ) );
			strcpy(tbase->ymd, ymd);
			tbase->next = NULL;
			node = tbase;
		} else {
			node = find_date(tbase, ymd);
		}

		if (node == NULL) {
			node = get_last(tbase);
			node->next = malloc( sizeof( struct Time ) );
			node = node->next;
			strcpy(node->ymd, ymd);
			node->next = NULL;
		}

		if (state) {
			node->in = dt;
		} else {
			node->out = dt;
		}

		fcheck = parse_line(fh, &state, &dt);
	}

	/* Go through the linked list and print it out. */
	node = tbase;
	while (node) {
		char  in[8] = "";
		char out[8] = "";
		float  diff = 0.0;

		strtime(in,  node->in);
		strtime(out, node->out);
		diff = (node->out).tm_hour - (node->in).tm_hour * 1.0;
		diff += ((node->out).tm_min - (node->in).tm_min * 1.0) / 100;

		printf("%s,%s,%s,%.02f\n", node->ymd, in, out, diff);

		last = node;
		node = node->next;
		free(last);
	}

	fclose(fh);

	return 0;
}


/* Parse a line from the log file into a tm struct and int. */
int parse_line(FILE * fh, int * s, struct tm * dt) {
	char ds[30] = "";
	int tmp = 0;
	int out = 0;

	out = fscanf(fh, "%d,%s\n", s, ds);
	sscanf(ds, "%d-%d-%dT%d:%d:%d-%n\n",
		&(dt->tm_year),
		&(dt->tm_mon),
		&(dt->tm_mday),
		&(dt->tm_hour),
		&(dt->tm_min),
		&(dt->tm_sec),
		&tmp
	);
	return out;
}


/* Look through the linked list and find a particular date. */
struct Time * find_date(struct Time * start, char * d) {
	struct Time * node = start;
	while (node != NULL) {
		if (strcmp(node->ymd, d) == 0) {
			break;
		} else {
			node = node->next;
		}
	}
	return node;
}


/* Return the last item in the list. */
struct Time * get_last(struct Time * start) {
	struct Time * last;
	while (start != NULL) {
		last = start;
		start = start->next;
	}
	return last;
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
