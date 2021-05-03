#include"minishell.h"

int	ft_checker(char **tmp, char *example, int start, int end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (start == 0 && tmp)
	{
		if (ft_strncmp(example, tmp[0], ft_strlen(tmp[0])) != 0)
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
	if (end == 0 && tmp[i - 1])
	{
		if (ft_strcmp(example + j - ft_strlen(tmp[i - 1]), tmp[i - 1]) != 0)
			return (1);
	}
	return (0);
}

int	regex_handler(char *regex, char *file)
{
	int		start;
	int		end;
	char	**tmp;

	start = 0;
	end = 0;
	if (regex[0] == '*')
		start = 1;
	if (regex[ft_strlen(regex) - 1] == '*')
		end = 1;
	tmp = ft_split(regex, '*');
	return (ft_checker(tmp, file, start, end));
}

int	check_star(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (0);
		i++;
	}
	return (1);
}

char	*check_path(char *arg, char **match)
{
	char	*result;

	(*match) = ft_strrchr(arg, '/');
	if (*match)
	{
		(*match)++;
		result = ft_trim_end(arg, *match);
	}
	else
	{
		(*match) = ft_strdup(arg);
		result = ft_strdup(".");
	}
	return (result);
}

void	check_cli_args(t_args **args)
{
	t_regex	reg;

	reg.id = 0;
	reg.tmp = *args;
	while (reg.tmp)
	{
		if (check_star(reg.tmp->arg) == 0)
		{
			reg.path = check_path(reg.tmp->arg, &reg.match);
			reg.directory = opendir(reg.path);
			reg_handler(&reg, args);
			if (reg.directory)
				closedir(reg.directory);
			if (reg.id == 1)
				delete_arg(args, reg.tmp->arg);
		}
		reg.tmp = reg.tmp->next;
	}
}
