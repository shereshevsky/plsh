#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>
#include <pwd.h>  
#define T 1
#define F 0

#define D T
#define INPUT_SIZE 128

/*	
*	fgets(char* A, READ_SIZE, stdin)
*		=>
*			"string\0" up to READ_SIZE, always 0-terminated
*/

void sfgetstdin(char* stored, int size) {
	fgets(stored, size, stdin);
	for (int k = size; k > -1; --k ) {
		if (stored[k] == '\n') {
			stored[k] = '\0';
			return;
		}
	}
}

int main(int argc, const char * argv[]) {

    char *path = strdup(getenv("PATH"));
    const char *const delim = ":";
    char *tok = NULL;
    char *rest = NULL;
    char *temp = NULL;
    char *dir_in_path = NULL;
    char *p = path;
    int i = 0;
    
    while((tok = strtok_r(p, delim, &rest))) {
        dir_in_path = strdup(tok);
        temp = strncat(dir_in_path, "/things", 100);
        printf("i: %s\n", temp);
        p = rest;
        free(temp);
        free(dir_in_path);
    }
//		sfgetstdin(inputLine, INPUT_SIZE);

    free(path);
    free(tok);
	return 0;
}
