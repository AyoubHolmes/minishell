#include "../includes/minishell.h"

void	list_help(char *elm1, char *elm2, t_element **list)
{
	if (elm1[ft_strlen(elm1) - 1] == '+')
		(*list)->next->obj2 = ft_strjoin((*list)->next->obj2,
				ft_strdup(elm2));
	else
	{
		ft_free_var ((*list)->next->obj2);
		(*list)->next->obj2 = ft_strdup(elm2);
	}
}

void	add_args(t_args *args_, char *cmd)
{
	t_args	*p;

	if (args_ == NULL)
	{
		args_ = (t_args *)malloc(sizeof(t_args));
		if (!(args_))
			return ;
		args_->arg = cmd;
		args_->next = NULL;
	}
	else
	{
		p = args_;
		while (p->next)
			p = p->next;
		p->next = (t_args *)malloc(sizeof(t_args));
		if (!(p->next))
			return ;
		p->next->arg = cmd;
		p->next->next = NULL;
	}
}

void	fill_dispatcher(t_minishell *shell)
{
	char	*(*command[8])(t_minishell *);

	shell->enviroment = ft_fill_shell_env(shell);
	if (shell->cmd != NULL && ft_strcmp(shell->cmd, "") != 0)
	{
		check_cli_cmd(&shell->cmd);
		check_cli_args(shell->args_tmp);
		shell->args = (*shell->args_tmp);
		check_cli_args(&shell->args);
		shell->er_id = 0;
		command[0] = ft_system;
		command[2] = pwd;
		command[1] = echo_;
		command[3] = cd;
		command[4] = export_;
		command[5] = unset;
		command[6] = env_;
		command[7] = exit_;
		command[shell->choice](shell);
		free_double_p(shell->enviroment);
	}
}
