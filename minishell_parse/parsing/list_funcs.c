#include "minishell.h"

int				dispatcher_id(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (2);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (3);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (4);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (6);
	if (ft_strncmp(cmd, "exit", 6) == 0)
		return (7);
	if (!ft_strncmp(cmd, "clear", 5))
		return (8);
	return (0);
}

void				insert_cmd(t_simple_cmd **s, char *cmd)
{
	t_args *p;

	if ((*s)->id == -1)
	{
		(*s)->cmd = cmd;
		(*s)->id = dispatcher_id(cmd);
	}
	else
	{
		if ((*s)->args == NULL)
		{
			
			(*s)->args = (t_args*)malloc(sizeof(t_args));
			(*s)->args->arg = cmd;
			(*s)->args->next = NULL;
		}
		else
		{
			p = (*s)->args;
			while(p->next)
				p = p->next;
			p->next = (t_args*)malloc(sizeof(t_args));
			p->next->arg = cmd;
			ft_putstr_parse("inside insert_cmd: ");
			ft_putstr_parse(p->next->arg);
			ft_putstr_parse("\n");
			p->next->next = NULL;
		}
	}
	
}

char			*arg_correction(char *s)
{
	int i;
	int j;

	i = 0;
	while (s[i])
	{
		if (s[i] == BACKSLASH_TOKEN || s[i] == SINGLE_QUOTE_TOKEN || s[i] == DOUBLE_QUOTE_TOKEN)
		{
			j = i;
			while (s[j])
			{
				s[j] = s[j + 1];
				j++;
			}
		}
		i++;
	}
	return (s);
}

t_simple_cmd	*create_simple_cmd_node(char *cmd)
{
	t_simple_cmd *s;
	int i;
	int size;
	int start;
	char *c;

	i = 0;
	start = 0;
	s = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	s->id = -1;
	s->args = NULL;
	s->next = NULL;
	while (cmd[i])
	{
		size = 0;
		while (cmd[i] && cmd[i] == ' ')
			i++;
		start = i;
		while (cmd[i] && cmd[i] != ' ')
		{
			if (cmd[i] == SINGLE_QUOTE_TOKEN || cmd[i] == DOUBLE_QUOTE_TOKEN)
			{
				size++;
				i++;
				while (cmd[i] && (cmd[i] != SINGLE_QUOTE_TOKEN || cmd[i] != DOUBLE_QUOTE_TOKEN))
				{
					size++;
					i++;
				}
			}
			size++;
			i++;
		}
		c = ft_substr(cmd, start, size);
		c = arg_correction(c);
		insert_cmd(&s, c);
		start = i + 1;
		if (cmd[i])
			i++;
	}
	return (s);
}

void	add_simple_cmd_node(t_simple_cmd **simple_cmd, char *cmd)
{
	t_simple_cmd *p;

	if (*simple_cmd == NULL)
		*simple_cmd = create_simple_cmd_node(cmd);
	else
	{
		p = *simple_cmd;
		while(p->next)
			p = p->next;
		p->next = create_simple_cmd_node(cmd);
	}
}

void	create_simple_cmd(char *line, int *i, int *start, t_simple_cmd **simple_cmd)
{
	char *cmd;
	int size;

	while (line[*i] && line[*i] != SEMICOLONE_TOKEN)
	{
		size = 0;
		while (line[*i] && line[*i] != PIPE_TOKEN)
		{
			if (line[*i] == SEMICOLONE_TOKEN)
				break;
			size++;
			(*i)++;
		}
		cmd = ft_substr(line, *start, size);
		*start = *i + 1;
		add_simple_cmd_node(simple_cmd, cmd);
		if (line[*i] != SEMICOLONE_TOKEN && line[*i])
			(*i)++;
	}
}