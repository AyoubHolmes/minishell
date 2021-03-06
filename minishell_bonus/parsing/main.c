#include "../includes/minishell.h"
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
	char	*s;

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
	cli->shlvl = catch_elem("SHLVL", &cli->shell);
	s = cli->shlvl->obj2;
	cli->shlvl->obj2 = ft_itoa(ft_atoi(cli->shlvl->obj2) + 1);
	ft_free_var(s);
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
	g_cli.is_empty_dollar = 0;
	signals_manager();
	while (cli->line[i])
	{
		create_simple_cmd(cli, &i, &start, &cli->simple_cmd);
		if (!cli->status && !cli->er_id && !errno)
			ft_pipe(cli);
		else
			cli->er_id = cli->status;
		free_simple_cmd(&cli->simple_cmd);
		cli->simple_cmd = NULL;
		if (cli->line[i])
			i++;
	}
}

void	init_(t_history **h, t_minishell *cli, char **env)
{
	*h = NULL;
	cli->simple_cmd = NULL;
	cli->enviroment = env;
	cli->old_stdin = dup(0);
	cli->old_stdout = dup(1);
	cli->old_stderror = dup(2);
	ft_exec_(cli);
	cli->er_id = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_history	*history;
	char		*tmp;

	init_(&history, &g_cli, env);
	prompt(0, g_cli.er_id);
	while (1)
	{
		g_cli.line = NULL;
		tmp = ft_readline(&history);
		if (tmp)
		{
			g_cli.line = ft_strtrim(tmp, " ");
			ft_lexer(&g_cli);
			lexer_debugger(&g_cli);
			if (g_cli.status == 0 && ft_strcmp(g_cli.line, "") != 0)
				ft_parser(&g_cli);
			ft_free_var(tmp);
			ft_free_var(g_cli.line);
			g_cli.line = NULL;
		}
		prompt(g_cli.status, g_cli.er_id);
	}
	return (0);
}
