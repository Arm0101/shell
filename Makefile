all: shell
	./shell 

shell: main.o list.o parser.o
	gcc -o shell main.o list.o parser.o
main.o: main.c
	gcc -c main.c

list.o: list.c list.h
	gcc -c list.c

parser.o: parser.c parser.h
	gcc -c parser.c

clean:
	rm -f shell *.o
