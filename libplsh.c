extern char *strdup(const char *s);
extern char *strtok(char *str, const char *delim);
extern char *strtok_r(char *str, const char *delim, char **saveptr);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern int gethostname(char *name, size_t len);

#define INPUT_SIZE 128
#define DEBUG 0
#define FDSTDIN  0
#define FDSTDOUT 1
#define FDSTDERR 2

/*  sfgetstdin
 *      strips newlines from fgets
 *      accepts char* string_to_put_result_in, int size_to_get
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

/*  count_tokens
 *      returns number of tokens in SPACE-DELIMITED string
 *      accepts C-string
 */

int count_tokens(char* input) {

    const char* DELIM = " ";
    int tokens = 1;
    char* next_tok = NULL;

    if (strlen(input) < 2)
        return 1;
    
    char* input_copy = strdup(input);
    
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

    char* buf = strdup(input);
    int i = 0;
    char *p;
    char** list = (char**) malloc(sizeof(char*) * toks + 1);

    if (strlen(input) < 2 || toks < 2) {
        list[0] = input;
        return list;
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

/* try_exec
 *      returns only with errors
 *      accepts C-string, should be pointer to args
 */

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
            return check_path;
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

/* prompt
 *      returns only bad things if it fails
 */

void prompt() {

    char* user = strdup(getenv("USER"));
    char cwd[512];
    char* cwd_success = NULL;
    cwd_success = getcwd(cwd, 512);       
            //could throw away getcwd return (same char* as first args)
    char host[512];
    int gotHost = gethostname(host, 512);
    
    if(user != NULL && gotHost != -1 && cwd_success != NULL) 
        printf("%s@%s:%s--)", user, host, cwd);

    free(user);
}

/* viewproc_builtin
 *      returns only bad things if it fails
 *      accepts C-string, should be name of a file in /proc
 */

void viewproc_builtin(char* procfile) {

    char proc_path[128];

    sprintf(proc_path, "/proc/%s", procfile);

    FILE* in = fopen(proc_path, "r");
    char buf[512];

    if (!in) {
        printf("Failed to open text file\n");
        return;
    }

    while(fgets(buf, 255, in) != NULL ){
        printf("%s", buf);
    }
}

/* cd_builtin
 *      accepts args[1]
 */

void cd_builtin (char dir[]) {

    char cwd[256];

            // same dir, do nothing
    if (strlen(dir) == 1 && dir[0] == '.')
        return;

    if (chdir(dir) == -1) 
        printf("There wuz a dir error\n");
    else if (getcwd(cwd, 512) && DEBUG)
        printf("%s\n", cwd);
}

/* envvar
 *      accepts (length of list, list of strings)
 *      returns on errors, just not meaningfully
 */

void envvar(int toks, char* tokens[]) {

    char* got_env;

    for (int i = 0; i < toks; i++) {
        
        if (tokens[i][0] == '$' 
            &&
            strlen(tokens[i]) > 1) {
            if ((got_env = getenv(tokens[i]+1)) != NULL) {
                //try to get the word as environment variable 
                //ignorning the $ (first char, not intelligent)

            if (DEBUG) printf("%s | %s\n", tokens[i], got_env);

            	tokens[i] = strdup(got_env);

        	} else {
        		tokens[i] = "";
        	}
        }
    }
}

/* perform_file_redir
 *      accepts (length of list, list of strings)
 *      returns on errors, with -1
 */

int perform_file_redir (int toks, char* args[]) {

    if (toks < 3)
        return 0;

    // redirect

    int fd_in_file, fd_out_file;
    int args_done = -1;

    if (toks >= 3) {
        for (int i = 0; i < toks; i++) {
            if (DEBUG) printf("checking for and doing redir\n");

            if (strcmp(args[i], "<") == 0) {
                // command reads from file a la "grep R < fileToGrep"
                if (DEBUG) printf("Opening file: %s\n", args[i+1]);

                if (args_done == -1) args_done = i;

                fd_in_file = open(args[i+1], O_RDONLY);
                if(fd_in_file == -1) {
                    printf("Malformed input or error opening the file for reading\n");
                    return -1;
                }
                dup2(fd_in_file, FDSTDIN);

            } else if (strcmp(args[i], ">") == 0) {
                // command reads from file a la "grep R > fileToOutput"
                if (DEBUG) printf("Opening file: %s\n", args[i+1]);

                if (args_done == -1) args_done = i;

                fd_out_file = open(args[i+1], O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG);
                if(fd_out_file == -1) {
                    printf("Malformed input or error opening the file for writing\n");
                    return -1;
                }
                dup2(fd_out_file, FDSTDOUT);
            }            
        }
    }

    // TODO only if argsdone not -1
    if (args_done != -1)
	    for(int i = args_done; i < toks; i++)
	        args[i] = '\0';

    return 0;
}
