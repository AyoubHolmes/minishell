#include "includes.h"

void ft_putstr(char *str,int fd)
{
	int i = 0;
	if(str == NULL)
	{
		write(1,"NULL",5);
		return;
	}
	while (str[i])
	{
		write(fd,&str[i],1);
		i++;
	}
}