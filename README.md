# TS
Time sheet program

## How this works
This just makes a log of in and out times. The log file is set by the
environment variable `$TSLOC`, or defaults to `~/Documents/ts`. `tkeep` logs the
time, and `tsheet` reads the log and outputs a time sheet in CSV format.

The log format uses `1` to indicate in and a `0` to indicate out (just remember
`1` looks like `i` and `0` looks like `o`), followed by the time and date in
ISO-8601 format. For example:

	1,2018-03-08T08:30:00-0500
	0,2018-03-08T16:30:00-0500
	1,2018-04-08T07:00:00-0500
	0,2018-04-08T15:00:00-0500

## Building
Before running make on this, please take a look at the `config.mk` file to
adjust settings for make and choose where to install. Some useful `make` targets
include:

- all
- test
- install
- clean

## Goals
I have a goal of learning more C, so I will be trying to re-write this as a full
C program. If anyone has suggestions on a better way to write portions of this
(standards, build process, etc), please feel free to make an issue or pull
request.
