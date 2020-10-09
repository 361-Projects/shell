/********************************************************
 * PROGRAM: Shell			                            *
 * CLASS: CISC 361-011                                  *
 * AUTHORS:                                             *
 *    Alex Sederquest | alexsed@udel.edu | 702414270    *
 *    Ben Segal | bensegal@udel.edu | 702425559         *
 ********************************************************/

#include "get_path.h"

/* where
 * Args:
 *      char *command: The command to be searched
 *      struct pathelement *p: a linked list of the path
 * Returns: int: the number of times the command was found in the path
 * Decription: Prints all occurnces of command found in p
 */
int where(char *command, struct pathelement *p) {
    char cmd[64], *ch;
    int found;

    found = 0;
    while (p) {
        sprintf(cmd, "%s/%s", p->element, command);
        if (access(cmd, X_OK) == 0) {
            found++;
            printf("%s\n",cmd);
        }
        p = p->next;
    }
    return found;
}
