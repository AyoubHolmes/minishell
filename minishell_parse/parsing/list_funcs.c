#include "minishell.h"

int     is_a_redirection_token(char *line)
{
	return (*line == REDIRECTION1_TOKEN || *line == REDIRECTION2_TOKEN || *line == REDIRECTION3_TOKEN);
}

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
	return (0);
}

int				insert_cmd(t_simple_cmd **s, char *cmd)
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
			
			if (!((*s)->args = (t_args*)malloc(sizeof(t_args))))
				return (6);
			(*s)->args->arg = cmd;
			(*s)->args->next = NULL;
		}
		else
		{
			p = (*s)->args;
			while(p->next)
				p = p->next;
			if (!(p->next = (t_args*)malloc(sizeof(t_args))))
				return (6);
			p->next->arg = cmd;
			p->next->next = NULL;
		}
	}
	return (0);
}

char			*arg_correction(char *s, t_element *env)
{
	int i;
	int j;
	t_element *env_var;
	char *tmp;
	char *dollar;

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
			i--;
		}
		if (s[i] == DOLLAR_TOKEN)
		{
			i++;
			j = 0;
			while(s[i] && s[i] != BACKSLASH_TOKEN && s[i] != SINGLE_QUOTE_TOKEN && s[i] != DOUBLE_QUOTE_TOKEN && s[i] != ' ')
			{
				j++;
				i++;
			}
			tmp = ft_substr(&s[i - j], 0, j);
			env_var = catch_elem(tmp, &env);
			if (!env_var || !env_var->obj2)
				dollar = "";
			else
				dollar = env_var->obj2;
			tmp = ft_strjoin(ft_substr(s, 0, i - j - 1), dollar);
			s = ft_strjoin(tmp, ft_substr(&s[i], 0, ft_strlen(s) - i));
			i = (i - j) + ft_strlen(dollar) - 1;
			i--;
		}
		i++;
	}
	return (s);
}

int		get_fd_file(char *cmd, int *i, t_simple_cmd **s, t_element *env)
{
	int start;
	int size;
	char *filename;
	char redirect;

	redirect = cmd[*i];
	(*i)++;
	if (cmd[*i] == REDIRECTION3_TOKEN)
		(*i)++;
	while (cmd[*i] && cmd[*i] == ' ')
		(*i)++;
	size = 0;
	while (cmd[*i] && cmd[*i] != ' ' && !is_a_redirection_token(&cmd[*i]))
	{
		(*i)++;
		size++;
	}
	filename = arg_correction(ft_substr(&cmd[(*i) - size], 0, size), env);
	if (redirect == REDIRECTION1_TOKEN)
		(*s)->out_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (redirect == REDIRECTION2_TOKEN)
		(*s)->in_fd = open(filename, O_RDONLY, 0666);
	else if (redirect == REDIRECTION3_TOKEN)
		(*s)->out_fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
	free(filename);
	if (errno != 0)
	{
		if (!(*s)->cmd)
			ft_putstr("minishell", 2);
		else	
			ft_putstr((*s)->cmd, 2);
		ft_putstr(": ", 2);
		ft_putstr(filename, 2);
		ft_putstr(": ", 2);
		ft_putstr(strerror(errno), 2);
		ft_putstr("\n", 2);
		return (9);
	}
	return (0);
}

t_simple_cmd			*simple_cmd_node_init()
{
	t_simple_cmd *s;

	s = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	s->id = -1;
	s->in_fd = 0;
	s->out_fd = 1;
	s->err_fd = 2;
	s->args = NULL;
	s->next = NULL;
	return (s);
}

t_simple_cmd	*create_simple_cmd_node(char *cmd, t_element *env, int *stat)
{
	t_simple_cmd *s;
	int i;
	int size;
	int start;
	char *c;
	

	i = 0;
	start = 0;
	s = simple_cmd_node_init();
	while (cmd[i])
	{
		size = 0;
		while (cmd[i] && cmd[i] == ' ')
			i++;
		start = i;
		while (cmd[i] && cmd[i] != ' ' && !is_a_redirection_token(&cmd[i]))
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
		if(is_a_redirection_token(&cmd[i]))
			*stat = get_fd_file(cmd, &i, &s, env);
		if (size != 0)
		{
			// c = ft_substr(cmd, start, size);
			c = arg_correction(ft_substr(cmd, start, size), env);
			*stat = insert_cmd(&s, c);
			start = i + 1;
		}
		if (cmd[i] && !(*stat))
			i++;
	}
	return (s);
}

int		add_simple_cmd_node(t_simple_cmd **simple_cmd, char *cmd, t_element *env)
{
	t_simple_cmd *p;
	int stat;

	stat = 0;
	if (*simple_cmd == NULL)
		*simple_cmd = create_simple_cmd_node(cmd, env, &stat);
	else
	{
		p = *simple_cmd;
		while(p->next)
			p = p->next;
		p->next = create_simple_cmd_node(cmd, env, &stat);
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
		stat = add_simple_cmd_node(simple_cmd, cmd, cli->shell);
		free(cmd);
		if (cli->line[*i] != SEMICOLONE_TOKEN && cli->line[*i] && !stat)
			(*i)++;
	}
	cli->status = stat;
}