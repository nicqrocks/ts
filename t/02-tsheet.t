#!/bin/bash

source `dirname $0`/tap.sh

#Vars to use for testing.
TSLOC=/tmp/ts.test
export TSLOC

TSCSV=/tmp/ts.csv
export TSCSV


#Make the TSLOC file.
cat <<END >$TSLOC
1,2018-03-06T07:00:00-0500
0,2018-03-06T15:00:00-0500
1,2018-03-07T08:15:00-0500
0,2018-03-07T16:15:00-0500
END

#Make sure the help bit works.
if [[ `./tsheet -h | grep -c "USAGE"` -eq 1 ]]; then
	ok "Got help message"
else
	nok "No help message given with -h"
fi

#Check if a file can be made.
./tsheet >$TSCSV
if [[ `cat $TSCSV | wc -l` -ne 0 ]]; then
	ok "File was writen to"
else
	nok "# TODO File is empty."
fi


rm $TSLOC
done-testing
