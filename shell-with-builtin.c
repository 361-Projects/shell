#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <glob.h>
#include <signal.h>
#include "sh.h"


const char *prompt = ">> ";
char prompt_prefix[MAXLINE];

int main(int argc, char **argv, char **envp)
{
	// Signal stuff
	sigignore(SIGTSTP);
	sigignore(SIGTERM);
	signal(SIGINT, signalHandler);

	printf("Welcome to sssh\nThe shell so bad it will make you mad\n");

	char buf[MAXLINE];
	char *arg[MAXARGS + 1]; // an array of tokens
	char *ptr;
	char *pch;
	char *last_dir = getcwd(NULL, 0);
	pid_t pid;
	glob_t paths;
	int status, i, arg_no, csource;

	printPrompt();
	while (1)
	{
		if (fgets(buf, MAXLINE, stdin) == NULL) {
			// ignoring control-d, which is eof
			printf(stdout, "Ignoring control-d, type \"exit\" to exit shell.");
			continue;
		}

		if (strlen(buf) == 1 && buf[strlen(buf) - 1] == '\n')
			goto nextprompt; // "empty" command line

		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */
		// parse command line into tokens (stored in buf)
		arg_no = 0;
		pch = strtok(buf, " ");
		while (pch != NULL && arg_no < MAXARGS)
		{
			if (strstr(pch, "*") != NULL) {
				csource = glob(pch, 0, NULL, &paths);	   
           		if (csource == 0) {
					for (char **p = paths.gl_pathv; *p != NULL; p++) {
						arg[arg_no] = (char *)malloc((int)strlen(*p)+1);
						strcpy(arg[arg_no], *p);
					}
                	globfree(&paths);
				}
			}
			else {
				arg[arg_no] = pch;
			}
			arg_no++;
			pch = strtok(NULL, " ");
		}
		arg[arg_no] = (char *)NULL;

		if (arg[0] == NULL) // "blank" command line
			goto nextprompt;

		if (strcmp(arg[0], "prompt") == 0)
		{
      		printf("Executing built-in [prompt]\n");
			set_prompt_prefix(arg, prompt_prefix);
		}
		else if (strcmp(arg[0], "kill") == 0) {
			kill_proc(arg);
		}
		else if (strcmp(arg[0], "pwd") == 0)
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
			int success;
			if (arg[1] == NULL) {
				// cd with nothing passed in
				free(last_dir);
				last_dir = getcwd(NULL, 0);
				success = chdir(getenv("HOME"));
			}
			else if (strcmp(arg[1], "-") == 0) {
				// cd to previous dir
				success = chdir(last_dir);
				free(last_dir);
				last_dir = getcwd(NULL, 0);
			} else {
				// normal path in cd
				free(last_dir);
				last_dir = getcwd(NULL, 0);
				success = chdir(arg[1]);
			}
			if (success >= 0) {
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
			printf("sssh PID: %d\n", getpid());
			goto nextprompt;
		}
		else if (strcmp(arg[0], "list") == 0) {
			printf("sssh: Executing built in [list]\n");
			if (arg[1] == NULL) {
				list("");
				goto nextprompt;
			}
			list(arg[1]);
		}
		else if (strcmp(arg[0], "where") == 0) {
			struct pathelement *p;
			char *cmd;

			printf("sssh: executing built-in [where]\n");

			if (arg[1] == NULL) {
				printf("where: Too few arguments.\n");
				goto nextprompt;
			}

			p = get_path();
			if(where(arg[1], p) == 0)
				printf("where: %s not found\n", arg[1]);
			free(p);
		}
		else if (strcmp(arg[0], "printenv") == 0) {
			printf("sssh: executing built-in [printenv]\n");
			printEnv(arg, envp);
		}
		else if (strcmp(arg[0], "setenv") == 0) {
			printf("sssh: executing built-in [setenv]\n");
			struct pathelement *p = get_path();
			setEnv(arg, envp, p);
			free(p);
		}
		else if (strcmp(arg[0], "exit") == 0) {
			printf("Exiting as requested\n");
			exit(0);
		}
		else
		{
			if ((pid = fork()) < 0)
			{
				printf("sssh: fork error\n");
			}
			else if (pid == 0)
			{ /* child */
				struct pathelement *p = get_path();
				char *cmd = which(arg[0], p);
				char flag = 1;

				if (cmd == NULL) {
					cmd = arg[0];
					flag = !flag;
				}
					

				execve(cmd, arg, envp);
				printf("sssh: couldn't execute: %s\nYou are bad and you should feal bad.\n", buf);
				free(p);
				if (flag)
					free(cmd);
				exit(127);
			}

			/* parent */
			if ((pid = waitpid(pid, &status, 0)) < 0)
				printf("sssh: waitpid error\n");
		}

	nextprompt:
		printPrompt();
	}
	exit(0);
}

void printPrompt() {
	if (prompt_prefix != NULL)
		printf("%s%s", prompt_prefix, prompt); /* print prompt (printf requires %% to print %) */
	else
		printf("%s", prompt);
}

void signalHandler(int signal) {
	if (signal == SIGINT) {
		// handle control c (by ignoring it)
		fprintf(stdout, "Ignoring control-c\n");
		printPrompt();
		fflush(stdout);
	}
}

void childSignalHandler(int signal) {
	if (signal == SIGCHLD) {
		fprintf(stdout, "no\n");
	}
}