#include "stdio.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void *GetStdHandle(unsigned int fd);

FILE *___stdin;
FILE *___stdout;
FILE *___stderr;

void __init_stdio(void)
{
	/* Allocate the file streams */
	___stdin = malloc(sizeof(FILE));
	___stdout = malloc(sizeof(FILE));
	___stderr = malloc(sizeof(FILE));

	/* Allocate the actual structures underneath */
	*___stdin = malloc(sizeof(struct file));
	*___stdout = malloc(sizeof(struct file));
	*___stderr = malloc(sizeof(struct file));

	/* Here, this uses GetStdHandle to get the handles */
	(*___stdin)->fd = GetStdHandle(-10);
	(*___stdout)->fd = GetStdHandle(-11);
	(*___stderr)->fd = GetStdHandle(-12);
}

#ifdef __cplusplus
}
#endif
