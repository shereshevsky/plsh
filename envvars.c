#include "libplsh.c"

int main (int argc, char* argv[]) {

	char input[INPUT_SIZE];

    char** args;
    int toks;


		sfgetstdin(input, INPUT_SIZE);
        toks = count_tokens(input);
        args = tokarr(input, toks);

    envvar(toks, args);

    for (int i = 0; i < toks; i++) {
    	
    	printf("%s\n", args[i]);

    }

    return 0;
}
