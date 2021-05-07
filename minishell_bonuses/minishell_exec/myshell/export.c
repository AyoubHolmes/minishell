#include "minishell.h"

void	edit_or_add(char *elm1, char *elm2, t_element **shell_)
{
	t_element	*list;
	char		**tmp;

	if (list == NULL)
		return ;
	list = *shell_;
	tmp = ft_split(elm1, '+');
	while (list->next)
	{
		if (ft_strcmp(list->next->obj1, tmp[0]) == 0)
		{
			list->next->id = 0;
			free_double_p(tmp);
			if (elm2 == NULL)
				return ;
			list_help(elm1, elm2, &list);
			return ;
		}
		list = list->next;
	}
	add_end(shell_, ft_strdup(tmp[0]), ft_strdup(elm2), 0);
	free_double_p(tmp);
}

char	**var_split(char *str)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * 3);
	while (str[i] && str[i] != '=')
		i++;
	res[0] = ft_substr(str, 0, i);
	if (str[i])
		res[1] = ft_substr(str, i + 1, ft_strlen(str));
	else
		res[1] = NULL;
	return (res);
}

void	export_to_liste(t_minishell *shell)
{
	t_args	*tmp;
	char	**str;

	tmp = shell->args;
	while (tmp)
	{
		if (check_identifier(tmp->arg, shell, 1, tmp->arg) == 1)
		{
			str = var_split(tmp->arg);
			edit_or_add(str[0], str[1], &shell->shell);
			free_double_p(str);
			str = NULL;
		}
		tmp = tmp->next;
	}
}

void	printer_export(t_element *list, t_minishell *shell_)
{
	if (list->id == 0)
	{			
		ft_putstr("declare -x ", shell_->out_fd);
		ft_putstr(list->obj1, shell_->out_fd);
		if (list->obj2)
		{
			ft_putstr("=\"", shell_->out_fd);
			ft_putstr(list->obj2, shell_->out_fd);
			ft_putstr("\"", shell_->out_fd);
		}
		ft_putstr("\n", shell_->out_fd);
	}
}

char	*export_(t_minishell *shell_)
{
	t_element	*p;
	t_element	*q;

	p = NULL;
	if (shell_->args != NULL)
		export_to_liste(shell_);
	else
	{
		filling(&p, shell_->shell);
		sort_l(p);
		q = p;
		while (p != NULL)
		{
			printer_export(p, shell_);
			p = p->next;
		}
		free_element(q);
	}
	close(shell_->out_fd);
	dup2(shell_->old_stdout, 1);
	dup2(shell_->old_stdin, 0);
	return ("");
}
