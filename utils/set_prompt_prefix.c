#include "set_prompt_prefix.h"

char* set_prompt_prefix(char** arg) {
    char* toks = strtok(arg, " ");
    printf("%s", toks);

    return "hi";
}