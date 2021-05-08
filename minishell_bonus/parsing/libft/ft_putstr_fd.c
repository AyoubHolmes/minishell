#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	index;

	if (s)
	{
		index = 0;
		while (s[index])
		{
			write(fd, &s[index], 1);
			index++;
		}
	}
}
