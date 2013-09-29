#include "libplsh.c"  
/*
    libplsh.c
    ---------
    sfgetstdin(char* stored, int size)
    count_tokens(char* input)
    tokarr (char input[], int toks)
    try_exec(char * input)
    
                    */



int main(int argc, const char * argv[]) {

	char* input_line = calloc(INPUT_SIZE, sizeof(char));
    char* found_exec;
    char** args;
    int toks;
    pid_t childpid;
    int childstat;

    // try_exec
    
	do {

        prompt();

		sfgetstdin(input_line, INPUT_SIZE);

        toks = count_tokens(input_line);
        args = tokarr(input_line, toks);

        if (args == NULL) {
            args = (char**) malloc(sizeof(char*));
            args[0] = input_line;

        }

        envvar(toks, args);

        for (int i = 0; i < toks; ++i) 
            printf(":%s\n", args[i]);

		if (DEBUG) {
            printf("you typed: |%s|\n", input_line);
		}

        if (strcmp(args[0], "cd") == 0) {
            cd_builtin(args[1]);
            continue;

        } else if (strcmp(args[0], "viewproc") == 0) {
            if (toks != 2) {
                printf("Please provide a (singular) proc to view\n");
                continue;
            }
            viewproc_builtin(args[1]);
            continue;

        } else if (strcmp(args[0], "exit") == 0) {
            printf("Exit\n");
			return 0;

		} else {
            found_exec = try_exec(args[0]);
            if (found_exec == NULL) {
                printf("Command not found in path\n");
                continue;
            }

            args[0] = found_exec;
            if (DEBUG) printf("EXEC:%s\n", found_exec);


            args[toks] = '\0'; 
            printf("\n\n%i\n\n", toks);

            for(int i = 0; i < toks + 1; i++)
                printf("EXEC: %i : %s\n", i, args[i]);

            // execv(found_exec, args);

                //splitting args for piping should happen here

            if((childpid = fork()) == 0) {
                //in child proc
                execv(found_exec, args);
            } else {
                childstat = wait(&childstat);
            }


        }
		input_line[0] =  '\0';
	} while (1);

    //never make it here?
	// free(input_line);
	return 0;
}
