#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>
#include <pwd.h>  

#define DEBUG 1

char* try_exec(char * input) {

    char* path = strdup(getenv("PATH"));
    const char* const DELIM = ":";
    const char* const SLASH = "/";
    char* tok = NULL;
    char* rest = NULL;
    char* check_path = calloc(500, sizeof(char));
    char* dir_in_path = NULL;
    char* p = path;
    char* command = strdup(input);
    int ok = -1;    
    while((tok = strtok_r(p, DELIM, &rest))) {
        dir_in_path = strdup(tok);
        sprintf(check_path, "%s%s%s", dir_in_path, SLASH, input);
        
        ok = access(check_path, X_OK);
        if (ok == 0) {
           //exec goes here
            if (DEBUG) 
                printf("i: %s\nx: %i\n\n", check_path, ok);
        
        }
            
        p = rest;
        free(dir_in_path);
    }
    
    free(path);
    free(tok);
    free(check_path);
    free(command);
	return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2)
        return -1;
    try_exec(argv[1]);
}
