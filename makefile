CC = gcc -Wall -pedantic --std=c99

all : plsh arrcat
arrcat :
	$(CC) -o Arrcat arrcat.c
plsh :
	$(CC) -o Plsh main.c
clean :	c-arr c-plsh
	
c-plsh :
	rm -rf *.o Plsh
c-arr :
	rm -rf *.o Arrcat
ra :
	./Arrcat
rp :
	./Plsh
