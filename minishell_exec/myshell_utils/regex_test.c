# include"minishell.h"

int	ft_find(char *str, char *look_for)
{
	int i = 0;
	int j = 0;

	while (str[i] !='\0')
	{
		if (str[i] == look_for[j] && look_for[j] !='\0')
		{
			j++;
			if (j == ft_strlen(look_for))
				return (i+1);
		}
		else
			j = 0;
		i++;
	}
	return (0);
}

int	ft_checker(char **tmp,char *example, int start, int end)
{
	int i = 0;
	int j = 0;
	int res = 0;
	if (start == 0 && tmp)
	{
		if (ft_strncmp(example,tmp[0],ft_strlen(tmp[0])) != 0)
			return (1);
		i++;
	}
	while (tmp[i])
	{
		example = example + j;
		j = ft_find(example, tmp[i]);
		if (j == 0)
			return (1);
		i++;
	}
	if (end == 0 && tmp[i-1])
	{
		if (ft_strncmp(example + j -ft_strlen(tmp[i-1]),tmp[i-1],ft_strlen(tmp[i-1])) != 0)
			return (1);
	}
	return (0);
}
int	regex_handler(char *regex, char *file)
{
	int start;
	int end;
	char **tmp;

	start = 0;
	end = 0;
	if (regex[0] == '*')
		start = 1;
	if (regex[ft_strlen(regex)-1] == '*')
		end = 1;
	tmp = ft_split(regex, '*');
	return (ft_checker(tmp, file, start,end));
}
int	check_star(char *str)
{
	int i;
	i = 0;

	while (str[i])
	{
		if (str[i] == '*'/*STAR_TOKEN*/)
			return (0);
		i++;
	}
	return (1);
}
char *check_path(char *arg,char **match)
{
	char *result;
	(*match) = ft_strrchr(arg,'/');
	if(*match)
	{
		(*match)++;
		result = ft_strtrim(arg,*match);
	}
	else
	{
		(*match) = ft_strdup(arg);
		result = ft_strdup(".");
	}
	return(result);
	
}
void	check_cli_args(t_args **args)
{
	struct dirent *entry;
	char *file;
	t_args *tmp;
	char *cwd;
	int id;
	DIR *directory;
	char *path;
	char *match;

	id = 0;
	tmp = *args;
	cwd = malloc(PATH_MAX);
	getcwd(cwd, PATH_MAX);
	while (tmp)
	{
		if (check_star(tmp->arg) == 0)
		{
			path = check_path(tmp->arg,&match);
			directory = opendir(path);
			while ((entry = readdir(directory)))
			{
				file =ft_strdup(entry->d_name);
				if (regex_handler(match,file) == 0)
				{
					add_args(*args,file);
					id = 1;
				}
			}
			if (directory)
				closedir(directory);
			if (id == 1)
				delete_arg(args,tmp->arg);
		}
		tmp = tmp->next;
	}
}