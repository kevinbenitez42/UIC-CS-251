
test:  header.c bst.o
	gcc -o test header.c bst.o

t0:  t0.c bst.o header.c
	gcc -g -o t0 t0.c bst.o

t1:  t1.c bst.o header.c
	gcc -g -o t1 t1.c bst.o

bst.o: bst.c bst.h
	gcc -g -c bst.c

clean:
	rm -f bst.o test *.exe t0 t1
