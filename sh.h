#include "./utils/get_path.h"
#include "./utils/set_prompt_prefix.h"

int pid;
char *which(char *command, struct pathelement *pathlist);
void list(char *dir);
void printenv(char **envp);

#define PROMPTMAX 64
#define MAXARGS   16
#define MAXLINE   128
