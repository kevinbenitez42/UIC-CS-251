
CC=gcc

FLAGS=-Wall

all: sq.o fdriver

sq.o: sq.h sq.c
	$(CC) $(FLAGS) -c sq.c

fdriver: driver.c sq.o
	$(CC) $(FLAGS) driver.c sq.o -lc -o fdriver

clean:
	rm -f *.o fdriver
