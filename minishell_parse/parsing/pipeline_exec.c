#include "minishell.h"
void	ft_fill_exec(t_minishell *cli,t_simple_cmd *tmp)
{

	cli->choice = tmp->id;
	cli->cmd = tmp->cmd;
	cli->args = tmp->args;
	cli->in_fd = tmp->in_fd;
	cli->out_fd = tmp->out_fd;
	cli->err_fd = tmp->err_fd;
	/* ft_putnbr_fd(tmp->in_fd,1);
	ft_putstr_parse("\n");
	ft_putnbr_fd(tmp->out_fd,1);
	ft_putstr_parse("\n");
	ft_putnbr_fd(tmp->err_fd,1);
	ft_putstr_parse("\n");
	ft_putstr_parse("----------------\n"); */
}
int process_(int in,int out, t_minishell *cli,t_simple_cmd *tmp)
{
	pid_t pid;
	pid = fork ();
	if (pid == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2 (out, 1);
			close (out);
		}
		
		ft_fill_exec(cli,tmp);
		fill_dispatcher(cli);
		exit(0);
	}
	wait(NULL);
	return(pid);
}
void ft_pipe(t_minishell *cli)
{
	t_simple_cmd * tmp;
	int in, fd [2];

	in = 0;
	tmp = cli->simple_cmd;
	if(!tmp->next)
	{
		ft_fill_exec(cli,tmp);
		fill_dispatcher(cli);
	}
	else
	{
		while(tmp->next)
		{
			pipe(fd);
			process_(in, fd[1], cli, tmp);
			close (fd[1]);
			in = fd[0];
			tmp = tmp->next;
		}
		process_(in, fd[1], cli, tmp);
	}
}