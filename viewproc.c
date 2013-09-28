#include "libplsh.c"

int main (int argc, char* argv[]) {

    if(argc < 2)
        return -1;

    viewproc_builtin(argv[1]);

    return 0;
}
