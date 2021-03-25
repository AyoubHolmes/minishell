#include "includes.h"

void ft_putstr(char *str,int fd)
{
	int i = 0;
	while (str[i])
	{
		write(fd,&str[i],1);
		i++;
	}
}