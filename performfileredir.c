#include "libplsh.c"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FDSTDIN  0
#define FDSTDOUT 1
#define FDSTDERR 2

int main (int argc, char* argv[]) {

    char*  inputLine = calloc(INPUT_SIZE, sizeof(char));
    char** args;
    char* found_exec;
    int toks;
    char cwd[512];
    char* cwd_success = getcwd(cwd, 512); 

    if (cwd_success)
        printf("%s\n", cwd);

    sfgetstdin(inputLine, INPUT_SIZE);

    toks = count_tokens(inputLine);
    args = tokarr(inputLine, toks);
    
    // redirect

    int fd_in_file, fd_out_file;
    int args_done = -1;

    for (int i = 0; i < toks; i++) {
	    if (toks >= 3) {
            printf("checking for and doing redir\n");

	        if (strcmp(args[i], "<") == 0) {
                // command reads from file a la "grep R < fileToGrep"
                if (DEBUG) printf("Opening file: %s\n", args[i+1]);
                fd_in_file = open(args[i+1], O_RDONLY);
                if(fd_in_file == -1) {
                    printf("There was an error opening the file for reading\n");
                    return -1;
                }
                dup2(fd_in_file, FDSTDIN);
                if (args_done == -1) args_done = i;

            } else if (strcmp(args[i], ">") == 0) {
                // command reads from file a la "grep R > fileToOutput"
                if (DEBUG) printf("Opening file: %s\n", args[i+1]);
                fd_out_file = open(args[i+1], O_CREAT | O_WRONLY);
                if(fd_out_file == -1) {
                    printf("There was an error opening the file for writing\n");
                    return -1;
                }
                dup2(fd_out_file, FDSTDOUT);
                if (args_done == -1) args_done = i;
            }            
	    }
    }

            found_exec = try_exec(args[0]);
            if (found_exec == NULL) {
                printf("Command not found in path\n");
                return -1;
            }

            args[0] = found_exec;
            // TODO only if argsdone not -1
            if (args_done != -1)
            for(int i = args_done; i < toks + 1; i++)
                args[i] = '\0';

            for(int i = 0; i < toks + 1; i++)
                printf("EXEC: %i : %s\n", i, args[i]);
    
            printf("\n\n%i\n\n", toks);

            execv(found_exec, args);

    // for (int i = 0; i < ts; i++) 
    //     printf("%s\n", arr[i]);

    return 0;
}
