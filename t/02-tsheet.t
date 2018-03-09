#!/bin/bash

source `dirname $0`/tap.sh

#Vars to use for testing.
TSLOC=/tmp/ts.test
export TSLOC

TSCSV=/tmp/ts.csv
export TSCSV


#Make the TSLOC file.
cat <<END >$TSLOC
1,2018-03-06T17:00:07-05:00
0,2018-03-07T08:30:07-05:00
1,2018-03-07T16:30:00-0500
0,2018-03-08T08:30:00-0500
END

#Make sure the help bit works.
if [[ `./tsheet | grep -c "USAGE"` -eq 1 ]]; then
	ok "No arg help message"
else
	nok "# TODO No help message given on no args"
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
