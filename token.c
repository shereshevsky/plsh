#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>
#include <pwd.h>  
#define T 1
#define F 0

#define DEBUG T


char** tokenize(char* input, char** result) {
    
    if (strlen(input) < 2)
        return NULL;
    
    char* input_copy = strdup(input);
    const char* DELIM = " ";
    char* tok = NULL;
    char* rest = NULL;
    char* p = input_copy;

    int tokens = 1;
    char* next_tok = NULL;
    
    for (next_tok = strchr(input_copy, DELIM[0]);
            next_tok != NULL;
            next_tok = strchr(next_tok + 1, DELIM[0])) {
        printf("%s\n", next_tok);
                tokens++;
    }
    printf("%i tokens\n", tokens);

    while(tok = strtok_r(p, DELIM, &rest)) {
        if (DEBUG) printf("i: %s\n", tok);
        p = rest;
    }

    free(input_copy);
	return 0;
}

int main (int argc, const char* argv[]) {
    char sample[] = "c1 a1 a2 a3";
    char** result = NULL;

    result = tokenize(sample, result);
}
