#include<stdio.h>
#include "libft.h"

int ft_checker(char **regex_split,char *example,char *regex)
{
	int i = 0;
	int j = 0;
	int res = 0;
	while(example[i])
	{
		if(regex)
		j = ft_find(example, regex_split[i]);
		if(j == 0)
			res = 1;
		i++;
	}
	return(res);
}

int main()
{
	int nb_star =0;
	char *regex = ft_strdup("*******ft*****d*.c****");
	nb_star = nb_of_a_star(regex);
	char *example = ft_strdup("llft_isdigit.cll");
	char **regex_split = ft_split(regex, '*');
	int res = ft_checker(regex_split, example, regex);
	ft_putnbr_fd(res,1);
}