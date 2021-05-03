#include<stdio.h>
#include "libft.h"
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

int	ft_find(char *str, char *look_for)
{
	int i = 0;
	int j = 0;
	
	while(str[i] !='\0')
	{
		if(str[i] == look_for[j] && look_for[j] !='\0')
		{
			j++;
			if(j == ft_strlen(look_for))
				return(i+1);
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

	if(end == 0 && tmp[i-1])
	{
		puts(tmp[i-1]);
		
		puts(example + j-ft_strlen(tmp[i-1]));
		if(ft_strcmp(example + j -ft_strlen(tmp[i-1]),tmp[i-1]) != 0)
			return(1);
	}
	return(0);
}
int regex_handler(char *regex, char *file)
{
	int start;
	int end;
	char **tmp;

	start = 0;
	end = 0;
	if(regex[0] == '*')
		start = 1;
	if(regex[ft_strlen(regex)-1] == '*')
		end = 1;
	tmp = ft_split(regex, '*');
	return(ft_checker(tmp, file, start,end));
}

int main(int argc,char **argv)
{
	struct dirent *entry;
	int files;
	char *file;

	char *cwd = malloc(PATH_MAX);
	getcwd(cwd, PATH_MAX);
	DIR *directory = opendir(ft_strdup("../libft/"));
	 while( directory && (entry=readdir(directory))  )
    {
        file = entry->d_name;
		if(regex_handler("*.c",file) == 0)
			printf("%s\n",file);
    }
	// closedir(directory);
}