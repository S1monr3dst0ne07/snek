

#include <stdio.h>
#include <stdlib.h>

#include "lex.c"


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("no source provided\n");
        exit(0);
    }

    char* src_path = argv[1];
    lex(src_path); 

}
