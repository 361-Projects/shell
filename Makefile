CC=gcc
VPATH = utils

sssh: get_path.o which.o set_prompt_prefix.o list.o shell-with-builtin.o
	$(CC) -g shell-with-builtin.c get_path.o which.o set_prompt_prefix.o list.o -o sssh

%.o: %.c
	$(CC) $< -c 

clean:
	rm -rf shell-with-builtin.o get_path.o which.o set_prompt_prefix.o list.o sssh
