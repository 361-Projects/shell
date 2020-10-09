/********************************************************
 * PROGRAM: Shell			                            *
 * CLASS: CISC 361-011                                  *
 * AUTHORS:                                             *
 *    Alex Sederquest | alexsed@udel.edu | 702414270    *
 *    Ben Segal | bensegal@udel.edu | 702425559         *
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>

void printEnv(char **arg, char **envp) {
    if (arg[2] != NULL) {
        fprintf(stderr, "%s", "printenv: too many arugments\n");
        return;
    }
    if (arg[1] == NULL) {
        for (int i = 0; envp[i] != NULL; i++) {
            printf("%s\n", envp[i]);
        }
        return;
    }
    if (getenv(arg[1]) != NULL) 
            printf(" %s\n", getenv(arg[1]));
    else 
        fprintf(stderr, "printenv: %s not found\n", arg[1]);
}