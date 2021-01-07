#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	write(1, "It actually f*cking works!\n", 28);

	return 0;
}
