#Configuration file for make

VERSION = 1.0

#Change the values below to match your needs.

#Install location
PREFIX = /usr/local

#Man page location
MANPREFIX = $(PREFIX)/share/man

#Flags
FLAGS = -DVERSION=\"$(VERSION)\" -std=c99

#Compiler
# CC = tcc
