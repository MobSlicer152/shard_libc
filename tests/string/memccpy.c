#include "unistd.h"
#include "string.h"

int main(void)
{
	char buf1[] = "asdfasdf";
	char buf2[9];
	char *f;

	/* This should return a pointer to buf1[4] or 'a' */
	f = memccpy(buf2, buf1, 'f', 4);
	
	return 0;
}
