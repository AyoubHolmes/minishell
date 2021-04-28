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

pid_t process_(int *fds,int *counter, t_minishell *cli,t_simple_cmd *tmp)
{
	pid_t pid;

	if(cli->nb_pipe == 0 && tmp->id != 0)
		pid = 0;
	else
		pid = fork();
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
		while(i < 2 * cli->nb_pipe)
		{
			close(fds[i]);
			i++;
		}
		//puts("IM HERE");
		ft_fill_exec(cli,tmp); // execute
		fill_dispatcher(cli); // execute
		if(cli->nb_pipe != 0 || tmp->id == 0 )
			exit(cli->status);
	}
	return (pid);
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
	int *fds;
	int *pid_status;
	int i;
	int counter;

	tmp = cli->simple_cmd;
	if(tmp->id == 7 && !tmp->next)
		ft_putstr("exit\n",1);
	cli->in_fd = dup(STDIN_FILENO);
	cli->out_fd = dup(STDOUT_FILENO);
	cli->nb_pipe = number_of_pipes(tmp) - 1;
	fds = malloc(cli->nb_pipe * 2 * sizeof(int));
	pid_status = malloc(cli->nb_pipe * sizeof(int));
	i = 0;
	while(i < cli->nb_pipe)
	{
        pipe(fds + i * 2);
		i++;
	}
	counter = 0;
	i = 0;
	while(tmp)
	{
		pid_status[i++] = process_(fds,&counter, cli, tmp);
		counter += 2;
		tmp = tmp->next;
	}
	i = 0;
	while(i < 2 * cli->nb_pipe)
	{
		close(fds[i]);
		i++;
	}
	i = 0;
	while(i < cli->nb_pipe + 1)
	{
		if(cli->nb_pipe == 0 && cli->simple_cmd->id != 0)
			break;
		waitpid(pid_status[i],&cli->wait_status,0);
		cli->status = WEXITSTATUS(cli->wait_status);
		i++;
	}
	free(fds);
	free(pid_status);
	fds = NULL;
	pid_status = NULL;

	dup2(STDOUT_FILENO, cli->out_fd);
	dup2(STDIN_FILENO, cli->in_fd);
	dup2(STDERR_FILENO, cli->err_fd);
}