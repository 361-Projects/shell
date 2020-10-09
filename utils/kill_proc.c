/********************************************************
 * PROGRAM: Shell			                            *
 * CLASS: CISC 361-011                                  *
 * AUTHORS:                                             *
 *    Alex Sederquest | alexsed@udel.edu | 702414270    *
 *    Ben Segal | bensegal@udel.edu | 702425559         *
 ********************************************************/

#include "kill_proc.h"

void kill_proc(char** args) {
    int pid;
    int signal;
    int kreturn;
    if (args[1] == NULL)
        fprintf(stderr, "Error: No process given\n");
    else if (args[2] != NULL) {
        // -9 part
        pid = atoi(args[2]);
        args[1][0] = ' ';
        signal = atoi(args[1]);
        // Error checks
        if (pid == 0) {
            fprintf(stderr, "Invalid PID");
            //perror("Invalid PID");
        } else if (signal == 0) {
            fprintf(stderr, "Invalid signal");
        } else {
            // Try to kill process
            kreturn = kill(pid, signal);
            if (kreturn != 0) {
                fprintf(stderr, "Kill failed");
            }
        }   
    } else {
        pid = atoi(args[1]);
        if (pid == 0) {
            fprintf(stderr, "Invalid PID");
        } else {
            kreturn = kill(pid, SIGTERM);
            if (kreturn != 0) {
                fprintf(stderr, "Kill failed");
            }
        }
    }
}