#!/bin/bash
#Time keeper program

#Make some vars.
if [[ $TSLOC == "" ]]; then
	TSLOC="$HOME/Documents/ts"
fi

#Help message
function help() {
	echo "USAGE: `basename $0` [-i|--in] [-o|--out]"
	exit 1
}

#Get the nearest quarter hour.
function gettime() {
	curdate=`date "+%s"`
	curquarter=$(($curdate - (($curdate - 7) % (15 * 60))))
	date -d"@$curquarter" -Isec
}

#Check for arguments given.
if [[ $# -eq 0 ]]; then help; fi
mkdir -p `dirname "$TSLOC"`
while [[ $# -gt 0 ]]; do
	case "$1" in
	'-h'|'--help')
		help
		;;
	'-i'|'--in')
		state=0
		;;
	'-o'|'--out')
		state=1
		;;
	*)
		echo "Arg $1 not recognized" 1>&2
		;;
	esac
	#Next argument
	shift
done

echo "$state,`gettime`" >>"$TSLOC"
