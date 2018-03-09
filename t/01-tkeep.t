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

#Make sure that tkeep can append to the file.
rm $TSLOC
./tkeep -i
./tkeep -o
if [[ `cat $TSLOC | wc -l` -eq 2 ]]; then
	ok "Can append to the file"
else
	nok "Only wrote" `cat $TSLOC | wc -l` "lines"
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
