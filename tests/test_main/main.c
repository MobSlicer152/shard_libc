#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	__syscall(__NR_write, 1, "asdf\n", 6);

	return 0;
}
