#include "../../includes/minishell.h"

t_simple_cmd	*simple_cmd_node_init(int *i, int *start)
{
	t_simple_cmd	*s;

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

t_simple_cmd	*create_simple_cmd_node(char *cmd, t_element *env,
			int *stat, int err_id)
{
	t_simple_cmd	*s;
	int				i;
	int				size;
	int				start;
	char			*c;

	s = simple_cmd_node_init(&i, &start);
	while (cmd[i])
	{
		size = 0;
		node_traversal(cmd, &i, &start, &size);
		if (is_a_redirection_token(&cmd[i]))
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

int	add_simple_cmd_node(t_simple_cmd **simple_cmd,
		char *cmd, t_minishell *cli)
{
	t_simple_cmd	*p;
	int				stat;

	stat = 0;
	if (*simple_cmd == NULL)
		*simple_cmd = create_simple_cmd_node(cmd, cli->shell, &stat,
				cli->er_id);
	else
	{
		p = *simple_cmd;
		while (p->next)
			p = p->next;
		p->next = create_simple_cmd_node(cmd, cli->shell, &stat, cli->er_id);
	}
	return (stat);
}

void	create_simple_cmd(t_minishell *cli, int *i,
	int *start, t_simple_cmd **simple_cmd)
{
	char	*cmd;
	int		size;
	int		stat;

	while (cli->line[*i] && cli->line[*i] != SEMICOLONE_TOKEN)
	{
		size = 0;
		stat = 0;
		while (cli->line[*i] && cli->line[*i] != PIPE_TOKEN)
		{
			if (cli->line[*i] == SEMICOLONE_TOKEN)
				break ;
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
