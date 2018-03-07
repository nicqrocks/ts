#Time keeper and reporter

include config.mk


all: tkeep

tkeep: tkeep.o
	$(CC) $(CFLAGS) -o tkeep tkeep.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm tkeep tkeep.o

test: tkeep
	prove -v

install: tkeep
	mkdir -p $(PREFIX)/bin
	cp -f tkeep $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/tkeep


.PHONY: all install test clean

