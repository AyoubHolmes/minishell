#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd = open("test", O_CREAT | O_RDWR, 0666);
    int x = dup2(fd, 1);
    printf("%s\n%d\n","Hello\n", x);
    return 0;
}
