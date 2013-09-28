#include "libplsh.c"

int main (int argc, char* argv[]) {

    char*  inputLine = calloc(INPUT_SIZE, sizeof(char));
    char** args;
    int toks;
    char cwd[512];
    char* cwd_success = getcwd(cwd, 512); 


    if (cwd_success)
        printf("%s\n", cwd);

    sfgetstdin(inputLine, INPUT_SIZE);

    toks = count_tokens(inputLine);
    args = tokarr(inputLine, toks);
    
    if (strcmp(args[0], "cd") == 0 && toks == 2) {
        printf("Call cd\n");
        

    }

    // for (int i = 0; i < ts; i++) 
    //     printf("%s\n", arr[i]);

    return 0;
}
