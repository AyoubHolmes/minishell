#include "../includes/minishell.h"

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

void	path_handler(t_minishell *shell, int id, int *i)
{
	struct stat		buff;
	char			*binary_path;
	char			**argv;

	if (shell->paths->id == 0 && id != 2 && !ft_strchr(shell->cmd, '/'))
	{
		binary_path = ft_strjoin(ft_strjoin(shell->path[*i],
					ft_strdup("/")), ft_strdup(shell->cmd));
	}
	else
		binary_path = shell->cmd;
	dup2(shell->out_fd, 1);
	dup2(shell->in_fd, 0);
	argv = fill_args(argv, shell->args, binary_path);
	execve(argv[0], argv, shell->enviroment);
	(*i)++;
}

void	system_help(t_minishell *shell, struct stat buff, int a)
{
	if (errno != 0)
	{
		ft_putstr("minishell: ", shell->err_fd);
		ft_putstr(shell->cmd, shell->err_fd);
		ft_putstr(" ", shell->err_fd);
		if (ft_strchr(shell->cmd, '/') != NULL)
		{
			ft_putstr(strerror(errno), shell->err_fd);
			ft_putstr("\n", shell->err_fd);
			if (a == 0 && !(buff.st_mode & S_IXUSR))
				exit(126);
		}
		else
		{
			ft_putstr("command not found", shell->err_fd);
			ft_putstr("\n", shell->err_fd);
		}
		exit(127);
	}
}

void	id_direc_error(t_minishell *shell)
{
	ft_putstr("minishell: ", shell->err_fd);
	ft_putstr(shell->cmd, shell->err_fd);
	ft_putstr(" is a directory \n", shell->err_fd);
	exit(126);
}

char	*ft_system(t_minishell *shell)
{
	int				i;
	int				a;
	struct stat		buff;
	int				id;

	id = 0;
	i = 0;
	shell->path = ft_split(shell->paths->obj2, ':');
	a = stat(shell->cmd, &buff);
	if (ft_strchr(shell->cmd, '/') && a == 0)
	{	
		if (a == 0 && (S_IFDIR & buff.st_mode))
			id_direc_error(shell);
		if (a == 0 && (S_IFREG & buff.st_mode))
			id = 2;
	}
	if (shell->path != NULL)
	{
		while (shell->path[i])
			path_handler(shell, id, &i);
	}
	system_help(shell, buff, a);
	return ("");
}
