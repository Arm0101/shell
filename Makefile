all: shell
	./shell 

shell: main.o list.o parser.o utils.o
	gcc -o shell main.o list.o parser.o utils.o
main.o: main.c
	gcc -c main.c

list.o: list.c list.h
	gcc -c list.c

parser.o: parser.c parser.h
	gcc -c parser.c

utils.o: utils.c utils.h
	gcc -c utils.c

clean:
	rm -f shell *.o
