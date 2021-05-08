#include "../includes/minishell.h"

int	is_a_redirection_token(char *line)
{
	return (*line == RED1_TOKEN || *line == RED2_TOKEN || *line == RED3_TOKEN);
}

int	dispatcher_id(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (2);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (3);
	if (ft_strcmp(cmd, "export") == 0)
		return (4);
	if (ft_strcmp(cmd, "unset") == 0)
		return (5);
	if (ft_strcmp(cmd, "env") == 0)
		return (6);
	if (ft_strcmp(cmd, "exit") == 0)
		return (7);
	return (0);
}

int	insert_arg(t_simple_cmd **s, char *cmd)
{
	t_args	*p;

	if ((*s)->args == NULL)
	{
		(*s)->args = (t_args *)malloc(sizeof(t_args));
		if (!(*s)->args)
			return (6);
		(*s)->args->arg = cmd;
		(*s)->args->next = NULL;
	}
	else
	{
		p = (*s)->args;
		while (p->next)
			p = p->next;
		p->next = (t_args *)malloc(sizeof(t_args));
		if (!p->next)
			return (6);
		p->next->arg = cmd;
		p->next->next = NULL;
	}
	return (0);
}

void	insert_first_cmd(t_simple_cmd **s, char *cmd)
{
	if (cmd)
		(*s)->cmd = cmd;
	else
	{
		(*s)->cmd = NULL;
	}
	(*s)->id = dispatcher_id(cmd);
}

int	insert_cmd(t_simple_cmd **s, char *cmd)
{
	t_args	*p;

	if ((*s)->id == -1)
		insert_first_cmd(s, cmd);
	else
		return (insert_arg(s, cmd));
	return (0);
}
