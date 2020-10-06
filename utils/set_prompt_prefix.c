#include "set_prompt_prefix.h"

char* set_prompt_prefix(char** arg, char** prefix) {
    // for(int i = 0; arg[i] != NULL; i++)
    // {
    //     printf("%s\n", arg[i]);
    // }
    //printf("%ld", sizeof(arg));
    if (arg[1] != NULL) {
        free(*prefix);
        *prefix = (char*)malloc(sizeof(arg));
        for (int i = 1; arg[i] != NULL; i++) {
            strcat(*prefix, arg[i]);
            strcat(*prefix, " ");
        }
        printf("%s\n", *prefix);
    }
    return 0;
}