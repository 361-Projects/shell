#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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