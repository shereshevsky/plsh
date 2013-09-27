#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>

#define DEBUG 0

#include "libplsh.c"

int main (int argc, char* argv[]) {

    if(argc < 2)
        return -1;

    viewproc_builtin(argv[1]);

    return 0;
}
