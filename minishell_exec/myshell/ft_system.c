#include "minishell.h"

char	*ft_system(t_minishell *shell)
{
	
	int		pid;
	char*	binary_path;
	int i = 0;
	pid = fork();
	if(pid == 0)
	{
		while(shell->path[i])
		{
			binary_path = ft_strjoin(shell->path[i],"/");
			binary_path = ft_strjoin(binary_path,shell->cmd);
			char *const argv[] = {binary_path,NULL};
			int j = execve(binary_path, argv, shell->enviroment);
			// ft_putnbr_fd(j, 1);
			if(j < 0)
				i++;
		}
		ft_putstr("ayoub-shell: ",1);
		ft_putstr(shell->cmd, 1);
		ft_putstr(": command not found\n", 1);
	}
	wait(0);
	return ("");
}

/*
char	*ft_system(t_minishell *shell)
{
	int		pid;
	char*	binary_path;
	struct stat buff;
	int i = 0;
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		//binary_path = NULL;
		while(shell->path[i])
		{
			//printf("youhou\n");
	
			printf("lol\n");
			binary_path = ft_strdup("/bin/ls");
			printf("%s\n", binary_path);
			// binary_path = ft_strjoin(ft_strdup(shell->path[i]),ft_strdup("/"));
			// binary_path	= ft_strjoin(ft_strdup(binary_path), ft_strdup(shell->cmd));
			char *const argv[] = {binary_path,NULL};
			if(!(stat(binary_path, &buff)))
				execve(binary_path, argv, shell->enviroment);
			//if(j == -1)
				i++;
		}
	}
	return ("");
}
*/