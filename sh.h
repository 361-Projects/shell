#include "./utils/get_path.h"
#include "./utils/list.h"
#include "./utils/where.h"
#include "./utils/printenv.h"
#include "./utils/setenv.h"

int pid;
char *which(char *command, struct pathelement *pathlist);
void list(char *dir);
void printenv(char **envp);

#define PROMPTMAX 64
#define MAXARGS   16
#define MAXLINE   128
