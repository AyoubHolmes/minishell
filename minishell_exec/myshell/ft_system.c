#include "includes.h"

char	*ft_system(t_minishell *shell)
{
	int		pid;
	char*	binary_path;
	binary_path = ft_strjoin(ft_strdup("/bin/"),ft_strdup(shell->cmd));
	pid = fork();
	if (pid > 0)
		wait(NULL);
	else
	{
		char *const argv[] = {binary_path,NULL};
		int i = execve(binary_path, argv, shell->enviroment);
		ft_putnbr_fd(i, 1);
		ft_putstr("\n",1);
	}
	return ("");
}