/********************************************************
 * PROGRAM: Shell			                            *
 * CLASS: CISC 361-011                                  *
 * AUTHORS:                                             *
 *    Alex Sederquest | alexsed@udel.edu | 702414270    *
 *    Ben Segal | bensegal@udel.edu | 702425559         *
 ********************************************************/

#include "set_prompt_prefix.h"

/* Name: set_prompt_prefix
 * Args: char** args - the arguments passed into the shell, char* prefix - the pointer to the prefix variable
 * Return: void
 * Description: It either sets the prefix to the passed in prefix via arg from the cmd line or this will
 * prompt the user to enter the prefix and then set it.
 */
void set_prompt_prefix(char** arg, char* prefix) {
    memset(prefix, 0, 128); // clear the prefix
    if (arg[1] != NULL) {
        for (int i = 1; arg[i] != NULL; i++) {
            strcat(prefix, arg[i]);
            strcat(prefix, " ");
        }
    } else {
        char buf[128];
        printf("Enter prompt prefix: ");
        fgets(buf, 128, stdin);
        buf[strlen(buf) - 1] = '\0';
        strcat(buf, " ");
        strcpy(prefix, buf);
    }
}