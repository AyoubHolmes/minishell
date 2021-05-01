#include<stdio.h>
#include "libft.h"

int	ft_find(char *str, char *look_for)
{
	int i = 0;
	int j = 0;

	while(str[i])
	{
		if(str[i] == look_for[j])
			j++;
		else
			j = 0;
	}
	if(j == ft_strlen(look_for));
		return(i);
	return(0);
}

int ft_checker(char **tmp,char *example)
{
	int i = 0;
	int j = 0;
	while(tmp[i])
	{
		j = ft_find(example + j, tmp[i]);
		if(j == 0)
			return(1);
		i++;
	} 
	return(0);
}

int main()
{
	char *regex = ft_strdup("ft*.c");
	char *example = ft_strdup("ft_isdigit.c");
	char **tmp = ft_split(regex, '*');
	int res = ft_checker(tmp,example);
	ft_putnbr_fd(res,1);
}