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

	char *inputLine = calloc(INPUT_SIZE, sizeof(char));
	char *user = strdup(getenv("USER"));
    char *path = strdup(getenv("PATH"));
    const char *const delim = ":";
    char *tok;
    char *rest;
    char *p = path;

    while((tok = strtok_r(p, delim, &rest))) {
        printf("i: %s\n", tok);
        p = rest;
    }

    char cwd[512];
    char host[512];
    char *wd = getcwd(cwd, 512);
    int gotHost = gethostname(host, 512);
    
    if(user != NULL) 
        printf("%s@", user);
    if(gotHost != -1) 
        printf("%s:", host);
    if(wd != NULL)
        printf("%s--) ", cwd);
    
    if (path == NULL) {
        path[0] = ' ';
        path[1] = '\0';
    }
    
    

    // For fully correct results, you must allocate the save_pointer
    //   // to be the length of the string you'll parse.
//    char *save = (char *) calloc(strlen(path), sizeof(char));

//    printf("%s\n", path);
    
  //  token = strtok_r(path, delim);
  //  printf("%s", token);


	do {
		sfgetstdin(inputLine, INPUT_SIZE);
		if (D) {
			printf("you typed: |%s|\n", inputLine);
		}
		if (inputLine[0] == 'x') {
			return -1;
		}
		inputLine[0] =  '\0';
	} while (1);

	free(inputLine);
	free(user);
    free(path);
    free(tok);
	return 0;
}
