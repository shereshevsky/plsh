#include "libplsh.c"

int main(int argc, const char * argv[]) {

	char* input_line = calloc(INPUT_SIZE, sizeof(char));
    char* found_exec;
    char** args;
    int toks;
    pid_t childpid;
    int childstat;
    int background_exec = -1;
    int fd_stdin = dup(0);
    int fd_stdout = dup(1);

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
        if (perform_file_redir(toks, args) == -1) {
            printf("There was an error with your command.\n");
            continue;
        }


		if (DEBUG) {
            printf("you typed: |%s|\n", input_line);
            for (int i = 0; i < toks; ++i) 
                printf(":%s\n", args[i]);
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

            args[toks] = '\0'; 

            //splitting args for piping should happen here

            childpid = fork();

            if(childpid == 0) {
                //in child proc
                execv(args[0], args);
                printf("There was an error executing\n");
            } else {
                //in parent
//                if (background_exec == -1)
                if (DEBUG) printf("Made it through fork\n");
                waitpid(childpid, &childstat, 0);
                dup2(fd_stdin, FDSTDIN);
                dup2(fd_stdout, FDSTDOUT);
    //            else
     //               waitpid(-1, &childstat, WNOHANG);
            }

        }

		input_line[0] =  '\0';
	} while (1);

    //never make it here?
	// free(input_line);
	return 0;
}
