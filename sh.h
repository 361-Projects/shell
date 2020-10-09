/********************************************************
 * PROGRAM: Shell			                            *
 * CLASS: CISC 361-011                                  *
 * AUTHORS:                                             *
 *    Alex Sederquest | alexsed@udel.edu | 702414270    *
 *    Ben Segal | bensegal@udel.edu | 702425559         *
 ********************************************************/

#include "./utils/get_path.h"
#include "./utils/set_prompt_prefix.h"
#include "./utils/list.h"
#include "./utils/where.h"
#include "./utils/printenv.h"
#include "./utils/setenv.h"
#include "./utils/kill_proc.h"

int pid;
char *which(char *command, struct pathelement *pathlist);
void list(char *dir);
void printenv(char **envp);
void printPrompt();
void signalHandler(int signal);

#define PROMPTMAX 64
#define MAXARGS   16
#define MAXLINE   128
