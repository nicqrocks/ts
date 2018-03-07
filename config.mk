#Configuration file for make

VERSION = 0.2

#Change the values below to match your needs.

#Install location
PREFIX = /usr/local

#Flags
CFLAGS = -DVERSION=\"$(VERSION)\" -std=c99

#Compiler
# CC = tcc

