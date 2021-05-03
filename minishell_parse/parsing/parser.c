#include "../../includes/minishell.h"

int     is_a_redirection_token(char *line)
{
	return (*line == RED1_TOKEN || *line == RED2_TOKEN || *line == RED3_TOKEN);
}

int				dispatcher_id(char *cmd)
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
	t_args *p;

	if ((*s)->args == NULL)
	{
		(*s)->args = (t_args*)malloc(sizeof(t_args));
		if (!(*s)->args)
			return (6);
		(*s)->args->arg = cmd;
		(*s)->args->next = NULL;
	}
	else
	{
		p = (*s)->args;
		while(p->next)
			p = p->next;
		p->next = (t_args*)malloc(sizeof(t_args));
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

int				insert_cmd(t_simple_cmd **s, char *cmd)
{
	t_args *p;

	if ((*s)->id == -1)
		insert_first_cmd(s, cmd);
	else
		return (insert_arg(s, cmd));
	return (0);
}

t_simple_cmd			*simple_cmd_node_init(int *i, int *start)
{
	t_simple_cmd *s;

	*i = 0;
	*start = 0;
	s = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	s->id = -1;
	s->cmd = NULL;
	s->in_fd = 0;
	s->out_fd = 1;
	s->err_fd = 2;
	s->args = NULL;
	s->next = NULL;
	return (s);
}

void	node_traversal(char *cmd, int *i, int *start, int *size)
{
	while (cmd[*i] && cmd[*i] == ' ')
			(*i)++;
	*start = *i;
	while (cmd[*i] && cmd[*i] != ' ' && !is_a_redirection_token(&cmd[*i]))
	{
		if (cmd[*i] == SQ_TOKEN || cmd[*i] == DQ_TOKEN)
		{
			(*size)++;
			(*i)++;
			while (cmd[*i] && (cmd[*i] != SQ_TOKEN && cmd[*i] != DQ_TOKEN))
			{
				(*size)++;
				(*i)++;
			}
		}
		(*size)++;
		(*i)++;
	}
}

t_simple_cmd	*create_simple_cmd_node(char *cmd, t_element *env, int *stat, int err_id)
{
	t_simple_cmd *s;
	int i;
	int size;
	int start;
	char *c;

	s = simple_cmd_node_init(&i, &start);
	while (cmd[i])
	{
		size = 0;
		node_traversal(cmd, &i, &start, &size);
		if(is_a_redirection_token(&cmd[i]))
			*stat = get_fd_file(cmd, &i, &s, env);
		else if (size != 0)
		{
			c = arg_correction(ft_substr(cmd, start, size), env, err_id);
			*stat = insert_cmd(&s, c);
			start = i + 1;
		}
		if (cmd[i] && !(*stat))
			i++;
	}
	return (s);
}

int		add_simple_cmd_node(t_simple_cmd **simple_cmd, char *cmd, t_minishell *cli)
{
	t_simple_cmd *p;
	int stat;

	stat = 0;
	if (*simple_cmd == NULL)
		*simple_cmd = create_simple_cmd_node(cmd, cli->shell, &stat, cli->er_id);
	else
	{
		p = *simple_cmd;
		while(p->next)
			p = p->next;
		p->next = create_simple_cmd_node(cmd, cli->shell, &stat, cli->er_id);
	}
	return (stat);
}

void	create_simple_cmd(t_minishell *cli, int *i, int *start, t_simple_cmd **simple_cmd)
{
	char *cmd;
	int size;
	int stat;

	while (cli->line[*i] && cli->line[*i] != SEMICOLONE_TOKEN)
	{
		size = 0;
		stat = 0;
		while (cli->line[*i] && cli->line[*i] != PIPE_TOKEN)
		{
			if (cli->line[*i] == SEMICOLONE_TOKEN)
				break;
			size++;
			(*i)++;
		}
		cmd = ft_substr(cli->line, *start, size);
		*start = *i + 1;
		stat = add_simple_cmd_node(simple_cmd, cmd, cli);
		free(cmd);
		cmd = NULL;
		if (cli->line[*i] != SEMICOLONE_TOKEN && cli->line[*i] && !stat)
			(*i)++;
	}
	cli->status = stat;
}