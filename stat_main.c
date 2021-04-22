#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd;
    struct stat *buf;
    int x;

    fd = open("Makefile", O_RDWR);
    x = stat("Makefile", buf);
    printf("%d --- %d --- %s\n", fd, x, strerror(errno));
    /* if (argc > 1)
    {
        
    } */
    return 0;
}
