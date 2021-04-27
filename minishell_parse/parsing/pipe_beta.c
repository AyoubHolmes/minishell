#include "minishell.h"
void	ft_fill_exec(t_minishell *cli,t_simple_cmd *tmp)
{
	cli->choice = tmp->id;
	cli->cmd = tmp->cmd;
	cli->args = tmp->args;
	cli->in_fd = tmp->in_fd;
	cli->out_fd = tmp->out_fd;
	cli->err_fd = tmp->err_fd;
}

void process_(int *fds,int *counter, t_minishell *cli,t_simple_cmd *tmp, int nb_pipe)
{
	pid_t pid;

	pid = fork ();
	if (pid == 0)
	{
		if (tmp->next)
		{

			dup2(fds[*counter + 1], 1);
		}
		if (*counter != 0 )
		{
				dup2(fds[*counter - 2], 0);
		}
		int i = 0;
		while(i < 2 * nb_pipe)
		{
			close(fds[i]);
			i++;
		}
		ft_fill_exec(cli,tmp); // execute
		fill_dispatcher(cli); // execute
	}
	return ;
}

int		number_of_pipes(t_simple_cmd *cmds)
{
	int i;
	t_simple_cmd *tmp;

	tmp = cmds;
	i = 0;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i++);
}

void ft_pipe(t_minishell *cli)
{
	t_simple_cmd *tmp;
	int nb_pipe;
	int *fds;
	int i;
	int counter;

	tmp = cli->simple_cmd;
	if(tmp->id == 7 && !tmp->next)
	{
		ft_putstr("exit\n",1);
		if(tmp->args && tmp->args->next)
			ft_putstr("bash: exit: too many arguments\n",tmp->err_fd);
		else
			exit(atoi(exit_(cli)));
	}
	cli->in_fd = dup(STDIN_FILENO);
	cli->out_fd = dup(STDOUT_FILENO);
	nb_pipe = number_of_pipes(tmp) - 1;
	fds = malloc(nb_pipe * 2 * sizeof(int));
	i = 0;
	while(i < nb_pipe)
	{
        pipe(fds + i * 2);
		i++;
	}
	counter = 0;
	while(tmp)
	{
		process_(fds,&counter, cli, tmp,nb_pipe);
		counter += 2;
		tmp = tmp->next;
	}
	i = 0;
	while(i < 2 * nb_pipe)
	{
		close(fds[i]);
		i++;
	}
	i = 0;
	while(i < nb_pipe + 1)
	{
		wait(0);
		i++;
	}
	dup2(STDOUT_FILENO, cli->out_fd);
	dup2(STDIN_FILENO, cli->in_fd);
	dup2(STDERR_FILENO, cli->err_fd);
}