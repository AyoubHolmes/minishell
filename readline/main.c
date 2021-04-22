#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <sys/errno.h>
#include <sys/ioctl.h>

int main(int argc, char const *argv[])
{
	int fd = 0;
	// int i = isatty(fd);
	printf("%d\n",ttyslot());
	perror("status: ");
	return 0;
}
