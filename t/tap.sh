#!/bin/bash

TAP_COUNT=0

done-testing() {
	echo "1..$TAP_COUNT"
}

ok() {
	TAP_COUNT=$((TAP_COUNT + 1))
	echo "ok $TAP_COUNT - $*";
}

nok() {
	TAP_COUNT=$((TAP_COUNT + 1))
	echo "not ok $TAP_COUNT - $*"
}

bail() {
	echo 'Bail out!' "$*"
}
