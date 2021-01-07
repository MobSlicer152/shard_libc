#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
#ifdef __linux__
	write(1, "It actually f*cking works!\n", 28);
#endif /* __linux__ */

	return 0;
}
