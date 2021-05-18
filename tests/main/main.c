#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	int i;

	/* Print the argument vector to ensure its correctness */
	for (i = 0; i < argc; i++) {
		/* The file descriptor/handle retrieval will eventually have a wrapper (the I/O system is shitwater right now) */
		fprintf(stdout, "%s\n", argv[i]);
	}

	/* Hang until Ctrl-C or the console is closed */
	while (1) {}

	return 0;
}
