extern char *strdup(const char *s);
extern char *strtok(char *str, const char *delim);
extern char *strtok_r(char *str, const char *delim, char **saveptr);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define DEBUG 1


/*  count_tokens
 *      returns number of tokens in SPACE-DELIMITED string
 *      accepts C-string
 */

int count_tokens(char* input) {
    const char* DELIM = " ";

    if (strlen(input) < 2)
        return -1;
    
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
    char** list = (char**) malloc(sizeof(char*) * toks);

    if (strchr(buf, ' ') == NULL) {
        printf("Not enough toks!\n");
        return NULL;
    }

    p = strtok (buf," ");  
    while (p != NULL) {
    
        if (DEBUG) printf("i: %i\n\t%s\n", i, p);

        list[i++] = strdup(p);
        p = strtok (NULL, " ");
    }

    free(buf);
    return list;
}

int main (int argc, char* argv[]) {
    char* string = calloc(512, sizeof(char*));

    if (fgets(string, 512, stdin) == NULL)
        return -1;

    int ts = count_tokens(string);

    char** arr = tokarr(string, ts);

    if (arr == NULL) {

        printf("Not enough tokens\n");
        return -1;
    }

    if (DEBUG) printf("length %i \n", ts);

    printf("%s\n", arr[0]);


    // for (int i = 0; i < ts; i++) 
    //     printf("%s\n", arr[i]);

    return 0;
}
