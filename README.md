# TS
Time sheet program

## How this works
This just makes a log of in and out times. The log file is set by the
environment variable `$TSLOC`, or defaults to `~/Documents/ts`. `tkeep` logs the
time, and `tsheet` reads the log and outputs a time sheet in CSV format.

## Building
Before running make on this, please take a look at the `config.mk` file to
adjust settings for make and choose where to install.
Some useful `make` targets include:
- all
- test
- install
- clean

## Goals
I have a goal of learning more C, so I will be trying to re-write this as a full
C program.
