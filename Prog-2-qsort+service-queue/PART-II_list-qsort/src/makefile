
# TODO:  add a rule for compiling qsort.c into qsort

io.o: list.h io.c io.h
	gcc -c io.c

llist.o: list.h llist.c
	gcc -c llist.c


qsort: qsort.c io.o llist.o
	gcc qsort.c llist.o io.o -o qsort


clean:  
	rm -f qsort *.o

