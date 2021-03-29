#include "minishell.h"

void ft_exec_(t_minishell *cli)
{
	char **var;
	int i = 0;
    while(cli->enviroment[i])
    {
    	var =ft_split(cli->enviroment[i],'=');
        i++;
    	fill_list(var,cli);
    }
	fill_dispatcher(*cli);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- && (*s1 || *s2))
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}



void    ft_parser(t_minishell *cli)
{
	int i;
	int size;
	int start;
	char *cmd;

	i = 0;
	start = 0;
	cli->simple_cmd = NULL;
	while (cli->line[i])
	{
		create_simple_cmd(cli->line, &i, &start, &cli->simple_cmd);
		simple_cmd_printer(cli->simple_cmd);
		//ft_fill_exec(cli);
		//ft_exec_(cli);
		if (cli->line[i])
			i++;
	}
}

void	free_args(t_args *args)
{
	t_args	*p;
	t_args	*q;

	p = args;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q->arg);
		q->arg = NULL;
	}
}

void	free_simple_cmd(t_simple_cmd *simple_cmd)
{
	t_simple_cmd *p;
	t_simple_cmd *q;

	p = simple_cmd;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free_args(q->args);
		free(q->cmd);
		q->cmd = NULL;
		free(q);
		q = NULL;
	}
}


int     main(int argc,char **argv,char **env)
{
	t_minishell cli;
	cli.simple_cmd = NULL;
	cli.enviroment = env;
    prompt(0);
    while(1)
    {
        get_next_line(&cli.line);
        ft_lexer(&cli);
        lexer_debugger(&cli);
		if (cli.status == 0)
			ft_parser(&cli);
		//free_pipline(&cli);
		prompt(cli.status);
	}
}
