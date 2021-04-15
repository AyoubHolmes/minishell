#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	conv;
	int		i;

	i = 0;
	conv = c;
	while (s[i] && s[i] != conv)
		i++;
	if (s[i] == conv)
		return ((char *)&s[i]);
	else
		return (0);
}
