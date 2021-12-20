all: stringProg


#compiled file of main
main.o: main.c declarations.h
	gcc -Wall -g -c main.c


stringProg: main.o
	gcc -Wall -g -o stringProg main.o


.PHONY: clean all
clean:
	rm -f *.o *.a *.so stringProg