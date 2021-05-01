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
				
				return(i+1);
			}
		}
		else
		{
			j = 0;
		}
		i++;
	}
		
	return(0);
}

int ft_checker(char **tmp,char *example, int len_star)
{
	int i = 0;
	int j = 0;

	while(tmp[i])
	{
		example = example + j;
		j = ft_find(example, tmp[i]);
		printf("----%d----\n",j);
		char *tmp = ft_substr(example,0,j);
			printf("%s\n",tmp);
		if(j == 0)
			return(1);
		i++;
	}
	return(0);
}

int nb_of_a_star(char *str)
{
	int i=0;
	int nb = 0;

	while(str[i])
	{
		if(str[i]== '*')
			nb++;
		i++;
	}
	return(nb);
}

int main()
{
	int nb_star =0;
	char *regex = ft_strdup("*ft*d*.c*");
	nb_star = nb_of_a_star(regex);
	char *example = ft_strdup("llft_isdigit.cll");
	char **tmp = ft_split(regex, '*');
	int res = ft_checker(tmp, example, nb_star);
	ft_putnbr_fd(res,1);
}