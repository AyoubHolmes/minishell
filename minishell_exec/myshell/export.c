#include "minishell.h"

void	edit_or_add(char *elm1, char *elm2, t_element **shell_)
{
	t_element	*list;

	list = *shell_;
	if (list == NULL)
		return ;
	while (list->next)
	{
		if (strcmp(list->next->obj1, elm1) == 0)
		{
			list->next->id = 0;
			if (elm2 == NULL)
				return ;
			list->next->obj2 = ft_strdup(elm2);
			return ;
		}
		list = list->next;
	}
	add_end(shell_, elm1, ft_strdup(elm2), 0);
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
	res[1] = ft_substr(str, i + 1, ft_strlen(str));
	if (str[i])
		res[1] = str + i + 1;
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
		if (tmp->arg[0] == '=')
		{
			ft_putstr("ayoub-shell: export: `", shell->err_fd);
			ft_putstr(tmp->arg, shell->err_fd);
			ft_putstr("': not a valid identifier\n", shell->err_fd);
			shell->status = 1;
		}
		str = var_split(tmp->arg);
		edit_or_add(str[0], str[1], &shell->shell);
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

	p = NULL;
	if (shell_->args != NULL)
		export_to_liste(shell_);
	else
	{
		filling(&p, shell_->shell);
		sort_l(p);
		while (p != NULL)
		{
			printer_export(p, shell_);
			p = p->next;
		}
	}
	close(shell_->out_fd);
	dup2(shell_->old_stdout, 1);
	dup2(shell_->old_stdin, 0);
	return ("");
}
