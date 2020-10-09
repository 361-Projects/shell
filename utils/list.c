/********************************************************
 * PROGRAM: Shell			                            *
 * CLASS: CISC 361-011                                  *
 * AUTHORS:                                             *
 *    Alex Sederquest | alexsed@udel.edu | 702414270    *
 *    Ben Segal | bensegal@udel.edu | 702425559         *
 ********************************************************/

#include "list.h"

void list(char *dir) {
    DIR *dp;
    struct dirent *dirp;
    if (strcmp(dir, "") == 0) {
        char *cwd = getcwd(NULL, 0);
        if ((dp = opendir(cwd)) == NULL)  {
            errno = ENOENT;
            perror("No cwd: ");
        }
        while ((dirp = readdir(dp)) != NULL)
            printf(" %s\n", dirp->d_name);
        free(cwd);
        closedir(dp);
    }
    else {
        if ((dp = opendir(dir)) == NULL) {
            errno = ENOENT;
            printf(" list: cannot access %s: %s\n", dir, strerror(errno));
            return; 
        }
        printf(" %s:\n", dir);
        while ((dirp = readdir(dp)) != NULL) {
            printf("    %s\n", dirp->d_name);
        }
        closedir(dp);
    }
}