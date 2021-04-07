#include "minishell.h"

t_element *catch_elem(char *elm1,t_element **shell_)
{
	t_element *list;

	list = *shell_;
	if(list == NULL)
		return(NULL);
	while(list->next)
	{
		if(strcmp(list->next->obj1,elm1) == 0)
				return (list->next);
		list = list->next;
	}
	return(NULL);
}
void ft_exec_(t_minishell *cli)
{
	char **var;
	int i = 0;
	
    while(cli->enviroment[i])
    {
    	var = ft_split(cli->enviroment[i],'=');
        i++;
    	fill_list(var,cli);
    }
	cli->shell = add_end(&cli->shell,"OLDPWD",NULL,sizeof(char *));
	cli->oldpwd = catch_elem("OLDPWD",&cli->shell);
	cli->path = ft_split(catch_elem("PATH",&cli->shell)->obj2,':');
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

void	ft_fill_exec(t_minishell *cli)
{

	cli->choice = cli->simple_cmd->id;
	cli->cmd = cli->simple_cmd->cmd;
	cli->args = cli->simple_cmd->args;
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
		/* dup2(cli->old_stdin, 0);
		dup2(cli->old_stdout, 1);
		dup2(cli->old_stderror, 2); */
		// ft_fill_exec(cli);
		//ft_exec_(cli);
		//fill_dispatcher(cli);
		free(cli->simple_cmd);
		cli->simple_cmd = NULL;
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

void	env_printer(t_minishell *cli)
{
	t_element *p;

	p = cli->shell;
	while(p)
	{
		ft_putstr_parse(p->obj1);
		ft_putstr_parse("\n");
		p = p->next;
	}
}

int     main(int argc,char **argv,char **env)
{
	t_minishell *cli;

	cli = (t_minishell *)malloc(sizeof(t_minishell));
	cli->simple_cmd = NULL;
	cli->enviroment = env;
	cli->old_stdin = dup(0);
	cli->old_stdout = dup(1);
	cli->old_stderror = dup(2);
	ft_exec_(cli);
	//env_printer(cli);
    prompt(0);
    while(1)
    {
        get_next_line(&cli->line);
        ft_lexer(cli);
       	lexer_debugger(cli);
		if (cli->status == 0)
			ft_parser(cli);
		prompt(cli->status); 
	}
}
