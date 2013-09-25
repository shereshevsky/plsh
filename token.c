#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>

#define DEBUG 0

/*  count_tokens
 *      returns number of tokens in SPACE-DELIMITED string
 *      accepts C-string
 */

int count_tokens(char* input) {
    const char* DELIM = " ";
    if (strlen(input) < 2)
        return NULL;
    
    char* input_copy = strdup(input);
    
    int tokens = 1;
    char* next_tok = NULL;
    
    for (next_tok = strchr(input_copy, DELIM[0]);
            next_tok != NULL;
            next_tok = strchr(next_tok + 1, DELIM[0])) {
        if (DEBUG) printf("%s\n", next_tok);
                tokens++;
    }
    if (DEBUG) printf("%i tokens\n", tokens);

    free(input_copy);
    return tokens;
}


/* tokarr
 *      returns pointer to array of strings
 *      accepts C-string, number of tokens in string
 */

char** tokarr (char input[], int toks) {

    if (strlen(input) < 2 || toks < 2)
        return NULL;

    char* buf = strdup(input);
    int i = 0;
    char *p;
    char** list = (char**) malloc(sizeof(char*) * 3);

    p = strtok (buf," ");  
    while (p != NULL) {
        list[i++] = strdup(p);
        p = strtok (NULL, " ");
    }

    free(buf);
    return list;
}

int main (int argc, char* argv[]) {
    char string[] = "th thi thing";
    char** arr = tokarr(string, count_tokens(string));


    for (int i = 0; i < count_tokens(string); ++i) 
        printf("%s\n", arr[i]);

}
