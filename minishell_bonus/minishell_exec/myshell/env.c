#include "../includes/minishell.h"

char	*ft_join_elm(t_element *p)
{
	char	*tmp;

	if (!p->obj2)
		tmp = ft_strjoin(ft_strdup(p->obj1),
				ft_strjoin(ft_strdup("="), ft_strdup("")));
	else
		tmp = ft_strjoin(ft_strdup(p->obj1),
				ft_strjoin(ft_strdup("="), ft_strdup(p->obj2)));
	return (tmp);
}

char	**ft_fill_shell_env(t_minishell *cli)
{
	int			len;
	t_element	*p;
	int			i;
	char		**tmp;

	p = cli->shell;
	len = 0;
	len = len_list_element(cli->shell);
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (p)
	{
		if (p->id == 0)
		{
			tmp[i] = ft_join_elm(p);
			i++;
		}
		p = p->next;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	*env_(t_minishell *shell_)
{
	t_element	*p;

	p = shell_->shell;
	if (shell_->args)
	{
		ft_putstr("env: ", shell_->err_fd);
		ft_putstr(shell_->args->arg, shell_->err_fd);
		ft_putstr(": No such file or directory\n", shell_->err_fd);
		shell_->er_id = 127;
		return ("");
	}
	while (p != NULL)
	{
		if (p->obj2 && p->id == 0)
		{
			ft_putstr(p->obj1, shell_->out_fd);
			ft_putstr("=", shell_->out_fd);
			ft_putstr(p->obj2, shell_->out_fd);
			ft_putstr("\n", shell_->out_fd);
		}
		p = p->next;
	}
	return ("");
}
