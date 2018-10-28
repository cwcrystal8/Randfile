all: randfile.o
	gcc randfile.o

randfile.o: randfile.c randfile.h
	gcc -c randfile.c

run:
	./a.out

clean:
	rm *.o
	rm newfile.txt
