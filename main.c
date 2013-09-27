#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>
#include <pwd.h>  
#define DEBUG 0

#include "libplsh.c"  
/*
    libplsh.c
    ---------
    sfgetstdin(char* stored, int size)
    count_tokens(char* input)
    tokarr (char input[], int toks)
    try_exec(char * input)
    
                    */


#define INPUT_SIZE 128


int main(int argc, const char * argv[]) {

	char*  inputLine = calloc(INPUT_SIZE, sizeof(char));
    char** args;
    int toks;

    // try_exec
    
	do {

        prompt();

		sfgetstdin(inputLine, INPUT_SIZE);

        toks = count_tokens(inputLine);
        // args = tokarr(inputLine, toks);

        // for (int i = 0; i < toks; ++i) 
        //     printf(":%s\n", args[i]);

		if (DEBUG) {
            printf("you typed: |%s|\n", inputLine);
		}

		if (strcmp(inputLine, "exit") == 0) {
            printf("Exit\n\n");
			return -1;
		}
		inputLine[0] =  '\0';
	} while (1);

    //never make it here?
	// free(inputLine);
	return 0;
}
