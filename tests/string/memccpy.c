#include "unistd.h"
#include "string.h"

int main(void)
{
	char buf1[] = "asdfasdf";
	char buf2[9];
	char *f;

	/* This should return a pointer to buf1[4] or 'a' */
	f = memccpy(buf2, buf1, 'f', 4);

	/* Print our results */
	write(1, "memccpy returned \"", 18);
	write(1, f, strlen(f));
	write(1, "\", and buf2 contains \"", 22);
	write(1, buf2, strlen(buf2));
	write(1, "\"\n", 2);
	
	return 0;
}
