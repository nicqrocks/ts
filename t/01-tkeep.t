#!/bin/bash

source `dirname $0`/tap.sh

#Make sure the help bit works.
if [[ `./tkeep | grep -c "USAGE"` -eq 1 ]]; then
	ok "No arg help message"
else
	nok "No help message given on no args"
fi

#Make sure that tkeep can append to the file.
rm ts
TSLOC=ts ./tkeep -i
TSLOC=ts ./tkeep -o
if [[ `cat ts | wc -l` -eq 2 ]]; then
	ok "Can append to the file"
else
	nok "Only wrote" `cat ts | wc -l` "lines"
fi

#Check if the dates are being made properly.
for d in `cut -d',' -f2 ts`; do
	if [[ `echo "$d" | wc -c` -eq `date +%FT%T%z | wc -c` ]]; then
		ok "$d"
	else
		nok "$d does not seem to be the right size"
	fi
done

rm ts
done-testing
