#include "minishell.h"

void	shell_reg_list(t_regex *reg, t_element **p)
{
	reg->path = check_path(reg->cmp_tmp, &reg->match);
	reg->directory = opendir(reg->path);
	(*p) = fill_list_files(reg->directory, reg->match);
	sort_l((*p));
}

t_element	*fill_list_files(DIR *direc, char *match)
{
	struct dirent	*entry;
	t_element		*files;

	files = NULL;
	entry = readdir(direc);
	while (entry)
	{
		if (match[0] != '.')
		{
			if (entry->d_name[0] == '.')
			{
				entry = readdir(direc);
				continue ;
			}
		}
		if (files == NULL)
			files = create_list(entry->d_name, NULL, 0);
		else
			files = add_end(&files, entry->d_name, NULL, 0);
		entry = readdir(direc);
	}
	ft_free_var(entry);
	return (files);
}

void	delete_arg_node(t_args **args, char *arg)
{
	t_args	*s;
	t_args	*p;
	t_args	*q;

	p = *args;
	q = *args;
	while (p)
	{
		if (ft_strcmp(p->arg, arg) == 0)
		{
			s = p;
			q->next = p->next;
			free(s);
			s = NULL;
			break ;
		}
		q = p;
		p = p->next;
	}
}
