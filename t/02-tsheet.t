#!/bin/bash

source `dirname $0`/tap.sh

#Vars to use for testing.
TSLOC=/tmp/ts.$BASHPID
export TSLOC

TSCSV=/tmp/csv.$BASHPID
export TSCSV

TSEXP=/tmp/csv.exp.$BASHPID
export TSEXP


#Make the TSLOC file.
cat <<END >$TSLOC
1,2018-03-06T07:00:00-0500
0,2018-03-06T15:00:00-0500
1,2018-03-07T08:15:00-0500
0,2018-03-07T16:30:00-0500
END

#Make the expected output.
cat <<END >$TSEXP
2018/03/06,07:00,15:00,8.00
2018/03/07,08:15,16:30,8.25
END

#Make sure the help bit works.
if [[ `./tsheet -h | grep -c "USAGE"` -eq 1 ]]; then
	ok "Got help message"
else
	nok "No help message given with -h"
fi

#Check if a file can be made.
./tsheet >$TSCSV
if [[ `cat $TSCSV | wc -l` -eq 2 ]]; then
	ok "File was writen to"
else
	nok "File is the wrong size. Got `cat $TSCSV | wc -l` lines."
fi

#Make sure that the times are being reported correctly.
diff -q "$TSCSV" "$TSEXP" >/dev/null
if [[ $? -eq 0 ]]; then
	ok "The CSV was made properly."
else
	nok `diff $TSCSV $TSEXP`
fi

#Check if the before and after arguments work.
diff -q <(./tsheet -a "2018/03/07") <(sed "2q;d" $TSEXP) >/dev/null
if [[ $? -eq 0 ]]; then
	ok "The '--after' arg works"
else
	nok "The '--after' arg gives" `./tsheet -a "2018/03/07"`
fi

diff -q <(./tsheet -b "2018/03/07") <(sed "1q;d" $TSEXP) >/dev/null
if [[ $? -eq 0 ]]; then
	ok "The '--before' arg works"
else
	nok "The '--before' arg gives" `./tsheet -b "2018/03/07"`
fi

rm $TSLOC
rm $TSCSV
rm $TSEXP
done-testing
