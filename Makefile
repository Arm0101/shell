all: shell
	./shell 

shell: main.o list.o parser.o utils.o execute.o jobs.o help.o
	gcc -o shell main.o list.o parser.o utils.o execute.o jobs.o help.o
main.o: main.c
	gcc -c main.c

list.o: list.c list.h
	gcc -c list.c

parser.o: parser.c parser.h
	gcc -c parser.c

utils.o: utils.c utils.h
	gcc -c utils.c

execute.o: execute.c execute.h
	gcc -c execute.c

jobs.o: jobs.c jobs.h
	gcc -c jobs.c

help.o: help.c help.h
	gcc -c help.c
clean:
	rm -f shell *.o *.t;clear
