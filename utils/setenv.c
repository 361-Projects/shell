/********************************************************
 * PROGRAM: Shell			                            *
 * CLASS: CISC 361-011                                  *
 * AUTHORS:                                             *
 *    Alex Sederquest | alexsed@udel.edu | 702414270    *
 *    Ben Segal | bensegal@udel.edu | 702425559         *
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_path.h"

/* setEnv
 * Args: 
 *      char **arg: args passed in from the shell
 *      char **envp: shell enviroment
 *      struct pathelement *pathList: a linked list of the path
 * Returns: int: status of if the path changed
 * Decription: allows an envirnment variable to be set
 */
int setEnv(char **arg, char **envp, struct pathelement *pathList) {
    int pathChanged = 0;
    if (arg[3] != NULL){
        fprintf(stderr, "%s", " setenv: Too many arguments.\n");
    }
    else if (arg[1] == NULL) {
        for (int i = 0; envp[i] != NULL; i++)
        {
            printf("%s\n", envp[i]);
        }
    }
    else if (arg[2] != NULL) {
        if (strcmp("PATH", arg[1]) == 0) {
            setenv("PATH", arg[2], 1); 
            pathChanged = 1;
        }
        else {
            setenv(arg[1], arg[2], 1);
        }
    }
    else { 
        if (strcmp(arg[1], "PATH") == 0) { 
            setenv("PATH", "", 1);
            pathChanged = 1;
        }
        else {
            setenv(arg[1], "", 1); 
        }
    }
    return pathChanged;
}