#include "minishell.h"

int	ft_find(char *str, char *look_for)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == look_for[j] && look_for[j] != '\0')
		{
			j++;
			if (j == ft_strlen(look_for))
				return (i + 1);
		}
		else
			j = 0;
		i++;
	}
	return (0);
}

void	reg_handler(t_regex *reg, t_args **args)
{
	t_element	*p;

	p = fill_list_files(reg->directory, reg->match);
	sort_l(p);
	while (p)
	{
		reg->file = ft_strdup(p->obj1);
		if (regex_handler(reg->match, reg->file) == 0)
		{
			if (ft_strcmp(reg->path, "."))
				add_args(*args, ft_strjoin(reg->path, reg->file));
			else
				add_args(*args, reg->file);
			reg->id = 1;
		}
		p = p->next;
	}
}

void	replace_star(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == STAR_TOKEN)
			(*str)[i] = '*';
		i++;
	}
}

void	check_cli_cmd(char **cmd)
{
	t_regex		reg;
	t_element	*p;

	reg.cmp_tmp = *cmd;
	if (check_star(reg.cmp_tmp) == 0)
	{
		reg.path = check_path(reg.cmp_tmp, &reg.match);
		reg.directory = opendir(reg.path);
		p = fill_list_files(reg.directory, reg.match);
		sort_l(p);
		while (p)
		{
			reg.file = ft_strdup(p->obj1);
			if (regex_handler(reg.match, reg.file) == 0)
			{
				if (ft_strcmp(reg.path, "."))
					*cmd = ft_strjoin(reg.path, reg.file);
				else
					*cmd = reg.file;
				return ;
			}
			p = p->next;
		}
		replace_star(cmd);
		if (reg.directory)
			closedir(reg.directory);
	}
}
