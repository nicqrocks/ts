#!/bin/bash

source `dirname $0`/tap.sh

#Make sure the help bit works.
if [[ `./tsheet | grep -c "USAGE"` -eq 1 ]]; then
	ok "No arg help message"
else
	nok "No help message given on no args"
fi


done-testing
