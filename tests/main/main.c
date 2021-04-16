#include <string.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	int loc;

	/* Unfourtunately, Window's write() takes a handle */
#ifdef _WIN32
	loc = -11; /* The value for the CONOUT$ handle */
#else
	loc = 1;
#endif

	write(loc, "Hello, world!\n", 15);
	return 0;
}
