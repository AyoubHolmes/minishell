#include<stdio.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*p;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (NULL);
	if (!(p = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (i < ft_strlen(s1))
	{
		p[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_find(char *str, char *look_for)
{
	int i = 0;
	int j = 0;
	int k = 0;
	
	while(str[i] !='\0')
	{
		if(str[i] == look_for[j] && look_for[j] !='\0')
		{
			j++;
			if(j == ft_strlen(look_for))
			{
				puts(ft_substr(str,0,i+1 -j));
				return(i+1);}
		}
		else
		{
			j = 0;
		}
		i++;
	}
	return(0);
}

int ft_checker(char **tmp,char *example, int start, int end)
{
	int i = 0;
	int j = 0;
	int res = 0;
	if(start == 0 && tmp)
	{
		if(ft_strncmp(example,tmp[0],ft_strlen(tmp[0])) != 0)
			return(1);
		i++;
	}
	while(tmp[i])
	{
		example = example + j;

		j = ft_find(example, tmp[i]);
		if(j == 0)
			return(1);
		i++;
	}
	if(end == 0 && tmp)
		if(ft_strncmp(example,tmp[i-1],ft_strlen(tmp[i-1])) != 0)
			return(1);
	return(0);
}

int nb_of_a_star(char *str)
{
	int i=0;
	int nb = 0;

	while(str[i])
	{
		if(str[i]== '*' && str[i + 1] != '*')
			nb++;
		i++;
	}
	return(nb);
}

int main()
{
	int nb_star =0;
	int start = 0;
	int end = 0;
	char *regex = ft_strdup("*ft*d*.c*");
	if(regex[0] == '*')
		start = 1;
	if(regex[ft_strlen(regex)-1] == '*')
		end = 1;
	nb_star = nb_of_a_star(regex);
	char *example = ft_strdup("llft_isdigit.cll");
	char **tmp = ft_split(regex, '*');
	int res = ft_checker(tmp, example, start,end);
	ft_putnbr_fd(res,1);
}