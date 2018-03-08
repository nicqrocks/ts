#Time keeper and reporter

include config.mk

BIN = tkeep tsheet
SRC = $(BIN:=.c)
OBJ = $(SRC:.c=.o)

debug:
	@echo $(BIN)
	@echo $(SRC)
	@echo $(OBJ)

all: $(BIN)

tkeep: tkeep.o ts.o
	$(CC) $(FLAGS) -o $@ $^

tsheet: tsheet.o ts.o
	$(CC) $(FLAGS) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(BIN) $(OBJ)

test: $(BIN)
	prove -v

install: $(BIN)
	mkdir -p $(PREFIX)/bin
	cp -f tkeep $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/tkeep


.PHONY: all install test clean

