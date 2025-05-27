all: cezar decezar

caesar.o: caesar.c caesar.h
	gcc -c caesar.c

libcaesar.a: caesar.o
	ar rcs libcaesar.a caesar.o

cezar: main_cezar.c libcaesar.a
	gcc main_cezar.c -L. -lcaesar -o cezar

decezar: main_decezar.c libcaesar.a
	gcc main_decezar.c -L. -lcaesar -o decezar

clean:
	rm -f *.o *.a cezar decezar
