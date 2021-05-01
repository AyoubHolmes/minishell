#include "../../includes/minishell.h"
#include "readline.h"

t_element	*catch_elem(char *elm1, t_element **shell_)
{
	t_element	*list;

	list = *shell_;
	if (list == NULL)
		return (NULL);
	while (list->next)
	{
		if (ft_strcmp(list->next->obj1, elm1) == 0)
			return (list->next);
		list = list->next;
	}
	return (NULL);
}

void	ft_exec_(t_minishell *cli)
{
	char	**var;
	int		i;

	i = 0;
	cli->shell = NULL;
	while (cli->enviroment[i])
	{
		var = ft_split(cli->enviroment[i], '=');
		i++;
		fill_list(var, cli);
		free(var);
		var = NULL;
	}
	cli->oldpwd = catch_elem("OLDPWD", &cli->shell);
	free(cli->oldpwd->obj2);
	cli->oldpwd->obj2 = NULL;
	cli->pwd = catch_elem("PWD", &cli->shell);
	cli->home = catch_elem("HOME", &cli->shell);
	cli->paths = catch_elem("PATH", &cli->shell);
}

void	free_args(t_args **args)
{
	t_args	*p;
	t_args	*q;

	p = *args;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q->arg);
		q->arg = NULL;
		free(q);
		q = NULL;
	}
}

void	free_simple_cmd(t_simple_cmd **simple_cmd)
{
	t_simple_cmd	*p;
	t_simple_cmd	*q;

	p = *simple_cmd;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free_args(&q->args);
		free(q->cmd);
		q->cmd = NULL;
		free(q);
		q = NULL;
	}
}

void	ft_parser(t_minishell *cli)
{
	int		i;
	int		size;
	int		start;
	char	*cmd;

	i = 0;
	start = 0;
	cli->simple_cmd = NULL;
	while (cli->line[i])
	{
		create_simple_cmd(cli, &i, &start, &cli->simple_cmd);
		if (!cli->status)
			ft_pipe(cli);
			// simple_cmd_printer(cli->simple_cmd);
		free_simple_cmd(&cli->simple_cmd);
		cli->simple_cmd = NULL;
		if (cli->line[i])
			i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	cli;
	t_history	*history;
	char		*tmp;

	history = NULL;
	cli.simple_cmd = NULL;
	cli.enviroment = env;
	cli.old_stdin = dup(0);
	cli.old_stdout = dup(1);
	cli.old_stderror = dup(2);
	ft_exec_(&cli);
	prompt(0);
	while (1)
	{
		cli.line = NULL;
		// get_next_line(&tmp);
		tmp = ft_readline(&history, &cli.status);
		if (tmp)
		{
			cli.line = ft_strtrim(tmp, " ");
			ft_lexer(&cli);
			lexer_debugger(&cli);
			if (cli.status == 0)
				ft_parser(&cli);
			free(tmp);
			tmp = NULL;
			free(cli.line);
			cli.line = NULL;
		}
		prompt(cli.status);
	}
	return (0);
}
