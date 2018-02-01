fakemake: fakemake.c hmap.h hmap_int.o
	gcc  -DIVAL -g fakemake.c hmap_int.o -o fakemake

hmap_int.o: hmap.c hmap.h
	gcc -DIVAL -c -g hmap.c -o hmap_int.o

hmap.o: hmap.c hmap.h
	gcc -c -g hmap.c

clean:
	rm -f *.o fakemake

