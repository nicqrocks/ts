#!/bin/bash

source `dirname $0`/tap.sh

#File to use for testing.
TSLOC=/tmp/ts.test
export TSLOC

#Make sure the help bit works.
if [[ `./tkeep | grep -c "USAGE"` -eq 1 ]]; then
	ok "No arg help message"
else
	nok "No help message given on no args"
fi

#Log an in and out time.
rm $TSLOC
./tkeep -i
./tkeep -o

#Make sure that tkeep can append to the file.
if [[ `cat $TSLOC | wc -l` -eq 2 ]]; then
	ok "Can append to the file"
else
	nok "Only wrote" `cat $TSLOC | wc -l` "lines"
fi

#Be sure that the in and out values are correct.
if [[ `sed "1q;d" $TSLOC | cut -d',' -f1` -eq 1 ]]; then
	ok "In value is 1"
else
	nok "In value is not 1. Got:" `sed "1q;d" $TSLOC`
fi

if [[ `sed "2q;d" $TSLOC | cut -d',' -f1` -eq 0 ]]; then
	ok "Out value is 0"
else
	nok "Out value is not 0. Got:" `sed "2q;d" $TSLOC`
fi


#Check if the dates are being made properly.
for d in `cut -d',' -f2 $TSLOC`; do
	if [[ `echo "$d" | wc -c` -eq `date +%FT%T%z | wc -c` ]]; then
		ok "$d"
	else
		nok "$d does not seem to be the right size"
	fi
done

rm $TSLOC
done-testing
