tkeep: tkeep.o
	cc -o tkeep tkeep.o

tkeep.o: tkeep.c
	cc -c tkeep.c

clean:
	rm tkeep tkeep.o

