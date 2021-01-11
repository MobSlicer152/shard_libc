#include "string.h"

int main(void)
{
	char buf1[] = "asdf";
	char buf2[5];

	memccpy(buf2, buf1, 'd', 4);
}
