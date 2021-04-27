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

void	path_handler(t_minishell *shell, int *a, int *i)
{
	struct stat		buff;
	char			*binary_path;
	char			**argv;

	*a = stat(shell->cmd, &buff);
	if (*a != 0 && shell->paths->id == 0)
	{
		binary_path = ft_strjoin(ft_strjoin(shell->path[*i], "/"), shell->cmd);
		*a = stat(binary_path, &buff);
	}
	else
		binary_path = shell->cmd;
	if (*a == 0)
	{
		argv = fill_args(argv, shell->args, binary_path);
		execve(argv[0], argv, shell->enviroment);
	}
	(*i)++;
}

char	*ft_system(t_minishell *shell)
{
	int	i;
	int	a;

	i = 0;
	shell->path = ft_split(shell->paths->obj2,':');
	if(shell->path == NULL)
	{
		ft_putstr("ayoub-shell: ", shell->err_fd);
		ft_putstr(shell->cmd, shell->err_fd);
		ft_putstr(" No such file or directory\n", shell->err_fd);
		exit(127);
	}
	while (shell->path[i])
		path_handler(shell, &a, &i);
	if (a < 0)
	{
		ft_putstr("ayoub-shell: ", shell->err_fd);
		ft_putstr(shell->cmd, shell->err_fd);
		ft_putstr(" command not found\n", shell->err_fd);
		exit(127);
	}
	return ("");
}
