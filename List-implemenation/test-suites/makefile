# these two lines specify make "variables"
# makes it easy to change to a different compiler and
# change the flags.  Notice the variables are "expanded"
# with a $ sign.
CC=gcc 
FLAGS=-Wall -std=c99

all: llist.o tests_pt1 tests_pt2 ll_tst ras_demo

ll_tst: llist.o ll_tst.c
	$(CC) $(FLAGS) ll_tst.c llist.o -o ll_tst

tests_pt1: llist.o tests_pt1.c
	$(CC) $(FLAGS) tests_pt1.c llist.o -o tests_pt1

tests_pt2: llist.o tests_pt1.c
	$(CC) $(FLAGS) tests_pt2.c llist.o -o tests_pt2

ras_demo: llist.o ras_demo.c
	$(CC) $(FLAGS) ras_demo.c llist.o -o ras_demo
	

llist.o: list.h llist.c
	$(CC) $(FLAGS) -c llist.c

clean:
	rm -f *.o ll_tst ras_demo tests_pt1 tests_pt2

