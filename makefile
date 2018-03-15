#Time keeper and reporter

include config.mk
BIN = tkeep tsheet


all: $(BIN)

tkeep: tkeep.o ts.o
	$(CC) $(FLAGS) -o $@ $^

tsheet: tsheet.o ts.o
	$(CC) $(FLAGS) -o $@ $^

t/00-ts.t: t/00-ts.o ts.o
	$(CC) $(FLAGS) -o t/00-ts.t t/00-ts.o ts.o

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(BIN) t/00-ts.t
	find . -name "*.o" | xargs rm

test: $(BIN) t/00-ts.t
	prove -f

install: $(BIN)
	mkdir -p $(PREFIX)/bin
	cp -f tkeep $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/tkeep
	cp -f tsheet $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/tsheet


.PHONY: all install test clean

