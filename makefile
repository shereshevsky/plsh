CC = gcc -Wall -pedantic --std=c99

all : plsh arrcat token
arrcat :
	$(CC) -o Arrcat arrcat.c
plsh :
	$(CC) -o Plsh main.c
token :
	$(CC) -o Token token.c
clean :	c-arr c-plsh c-tok
	
c-plsh :
	rm -rf *.o Plsh
c-tok :
	rm -rf *.o Token
c-arr :
	rm -rf *.o Arrcat
ra :
	./Arrcat
rt :
	./Token
rp :
	./Plsh
