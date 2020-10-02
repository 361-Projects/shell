CC=gcc
VPATH = utils

mysh: get_path.o which.o shell-with-builtin.o
	$(CC) -g shell-with-builtin.c get_path.o which.o -o mysh

%.o: %.c
	$(CC) $< -c 

clean:
	rm -rf shell-with-builtin.o get_path.o which.o mysh
