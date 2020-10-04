#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "sh.h"

int main(int argc, char **argv, char **envp)
{
	char buf[MAXLINE];
	char *arg[MAXARGS]; // an array of tokens
	char *ptr;
	char *pch;
	pid_t pid;
	int status, i, arg_no;

	printf(">> "); /* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (strlen(buf) == 1 && buf[strlen(buf) - 1] == '\n')
			goto nextprompt; // "empty" command line

		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */
		// parse command line into tokens (stored in buf)
		arg_no = 0;
		pch = strtok(buf, " ");
		while (pch != NULL && arg_no < MAXARGS)
		{
			arg[arg_no] = pch;
			arg_no++;
			pch = strtok(NULL, " ");
		}
		arg[arg_no] = (char *)NULL;

		if (arg[0] == NULL) // "blank" command line
			goto nextprompt;

		if (strcmp(arg[0], "pwd") == 0)
		{ // built-in command pwd
			printf("Executing built-in [pwd]\n");
			ptr = getcwd(NULL, 0);
			printf("%s\n", ptr);
			free(ptr);
		}
		else if (strcmp(arg[0], "cd") == 0)
		{
			// cd cmd
			printf("Executing built-in [cd]\n");
			printf("%s\n", arg[1]);
			int success = chdir(arg[1]);
			if (success) {
				printf("Directory change successful\n");
			} else {
				printf("Directory change failed\n");
			}
		}
		else if (strcmp(arg[0], "which") == 0)
		{ // built-in command which
			struct pathelement *p, *tmp;
			char *cmd;

			printf("Executing built-in [which]\n");

			if (arg[1] == NULL)
			{ // "empty" which
				printf("which: Too few arguments.\n");
				goto nextprompt;
			}

			p = get_path();

			cmd = which(arg[1], p);
			if (cmd)
			{
				printf("%s\n", cmd);
				free(cmd);
			}
			else // argument not found
				printf("%s: Command not found\n", arg[1]);

			while (p)
			{ // free list of path values
				tmp = p;
				p = p->next;
				free(tmp->element);
				free(tmp);
			}
		}
		else if (strcmp(arg[0], "pid") == 0) {
			printf("Shell PID: %d\n", getpid());
			goto nextprompt;
		}
		else if (strcmp(arg[0], "exit") == 0) {
			printf("Exiting as requested\n");
			exit(0);
		}
		else
		{
			if ((pid = fork()) < 0)
			{
				printf("fork error\n");
			}
			else if (pid == 0)
			{ /* child */
				struct pathelement *p = get_path();
				char *cmd = which(arg[0], p);
				execve(cmd, arg, envp);
				printf("couldn't execute: %s\n", buf);
				free(p);
				free(cmd);
				//exit(127);
			}

			/* parent */
			if ((pid = waitpid(pid, &status, 0)) < 0)
				printf("waitpid error\n");
		}

	nextprompt:
		printf(">> ");
	}
	exit(0);
}
