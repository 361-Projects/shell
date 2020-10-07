#include "get_path.h"

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
