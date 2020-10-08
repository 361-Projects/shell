CC=gcc
VPATH = utils

sssh: get_path.o which.o set_prompt_prefix.o list.o where.o printenv.o setenv.o kill_proc.o shell-with-builtin.o
	$(CC) -g shell-with-builtin.c get_path.o which.o set_prompt_prefix.o list.o where.o printenv.o setenv.o kill_proc.o -o sssh

%.o: %.c
	$(CC) $< -c 

clean:
	rm -rf *.o sssh

run: sssh
	./sssh
