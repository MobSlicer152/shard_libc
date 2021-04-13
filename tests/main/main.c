#include <string.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	write(1, "Hello, world!\n", 15);
	return 0;
}
