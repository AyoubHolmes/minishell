#include "minishell.h"

int	len_list(t_args *arg)
{
	t_args	*p;
	int		i;

	p = arg;
	i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}

char	**fill_args(char **argv, t_args *elm, char *binary)
{
	int		i;
	t_args	*tmp;
	int		len;

	len = len_list(elm);
	argv = (char **)malloc((len * sizeof(char *)) + 2);
	argv[0] = binary;
	if (len == 0)
	{
		argv[1] = NULL;
		return (argv);
	}
	i = 1;
	tmp = elm;
	while (tmp)
	{
		argv[i] = tmp->arg;
		tmp = tmp->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	*ft_system(t_minishell *shell)
{	
	int			pid;
	char		*binary_path;
	char		**argv;
	int			i;
	struct stat	buff;
	int			a;

	//pid = fork();
	//if (pid == 0)
	//{
		i = 0;
		while (shell->path[i])
		{
			if ((a = stat(shell->cmd, &buff)) != 0 && shell->paths->id == 0)
			{
				binary_path = ft_strjoin(ft_strjoin(shell->path[i], "/"), shell->cmd);
				a = stat(binary_path, &buff);
			}
			else
				binary_path = shell->cmd;
			if (a == 0)
			{
				dup2(shell->out_fd, 1);
				dup2(shell->in_fd, 0);
				argv = fill_args(argv, shell->args, binary_path);
				execve(argv[0], argv, shell->enviroment);
				close(shell->out_fd);
				close(shell->in_fd);
			}
			i++;
		}
		if (a < 0)
		{
			shell->status = 10;
			ft_putstr("ayoub-shell: ", shell->err_fd);
			ft_putstr(shell->cmd, shell->err_fd);
			ft_putstr(" ", shell->err_fd);
			ft_putstr(strerror(errno), shell->err_fd);
			ft_putstr("\n", shell->err_fd);
		}
		//exit(0);
	//}
	//wait(0);
	dup2(shell->old_stdout, 1);
	dup2(shell->old_stdin, 0);
	return ("");
}
