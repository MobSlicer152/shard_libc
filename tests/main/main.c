#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	/* The file descriptor/handle retrieval will eventually have a wrapper */
	write((*stdout)->fd, "Hello, world!\n", 15);

	/* Hang until Ctrl-C or the console is closed */
	while (1) {}

	return 0;
}
