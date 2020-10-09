/********************************************************
 * PROGRAM: Shell			                            *
 * CLASS: CISC 361-011                                  *
 * AUTHORS:                                             *
 *    Alex Sederquest | alexsed@udel.edu | 702414270    *
 *    Ben Segal | bensegal@udel.edu | 702425559         *
 ********************************************************/

#include "get_path.h"

char *which(char *command, struct pathelement *p)
{
  char cmd[64], *ch;
  int  found;

  found = 0;
  while (p) {       
    sprintf(cmd, "%s/%s", p->element, command);
    if (access(cmd, X_OK) == 0) {
      found = 1;
      break;
    }
    p = p->next;
  }
  if (found) {
    ch = malloc(strlen(cmd)+1);
    strcpy(ch, cmd);
    return ch;
  }
  else
    return (char *) NULL;
}
