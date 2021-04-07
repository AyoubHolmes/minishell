#include "minishell.h"

int len_list(t_args *arg)
{
	t_args *p = arg;
	int i = 0;
	while(p)
	{
		p = p->next;
		i++;
	}
	return(i);
}
//delete the part below this line 
void	ft_args_printer(char **args, int size)
{
	int i = 0;
	while(i < size)
	{
		puts(args[i]);
		i++;
	}
}
//delete the above

char **fill_args(char **argv,t_args *elm, char *binary)
{
	int i;
	t_args *tmp;
	int len;

	len =len_list(elm);
	argv = (char **)malloc((len * sizeof(char *)) + 2);
	argv[0] = binary;
	if(len == 0)
	{
		argv[1] = NULL;
		return(argv);
	}
	i = 1;
	tmp = elm;
	while(tmp)
	{
		argv[i] = tmp->arg;
		tmp = tmp->next;
		i++;
	}
	argv[i] = NULL;
	return(argv);
}


char	*ft_system(t_minishell *shell)
{	
	int		pid;
	char*	binary_path;
	char **argv;
	int i;
	struct stat buff;
	int a;

	pid = fork();
	if(pid == 0)
	{
		i = 0;
		while(shell->path[i])
		{	
			binary_path = ft_strjoin(ft_strjoin(shell->path[i],"/"),shell->cmd);
			a = stat(binary_path, &buff);
			if(a == 0)
			{
				argv = fill_args(argv,shell->args, binary_path);
				execve(argv[0], argv, shell->enviroment);
			}
			i++;
		}
		if(a < 0)
		{
			shell->status = 8;
			ft_putstr("ayoub-shell: ",1);
			ft_putstr(shell->cmd, 1);
			ft_putstr(": command not found\n", 1);
		}
		exit(0);
	}
	wait(0);
	return ("");
}