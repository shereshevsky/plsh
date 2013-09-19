CC = gcc -Wall -pedantic --std=c99

all : 
	$(CC) -o plsh main.c
clean :
	rm -rf *.o plsh
r :
	./plsh
