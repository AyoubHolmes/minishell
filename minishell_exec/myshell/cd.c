#include "minishell.h"

void	edit_elem(char *elm1, char *elm2, t_element **shell_)
{
	t_element	*list;

	list = *shell_;
	if (list == NULL)
		return ;
	while (list->next)
	{
		if (strcmp(list->next->obj1, elm1) == 0)
		{
			list->next->obj2 = elm2;
			return ;
		}
		list = list->next;
	}
}

char	*ft_cases(t_minishell *shell, char *oldpwd)
{
	DIR	*folder;

	folder = opendir(oldpwd);
	if (!shell->args || strcmp(shell->args->arg, "~") == 0
		|| strcmp(shell->args->arg, "~/") == 0)
		return (shell->home->obj2);
	else if (strcmp(shell->args->arg, "-") == 0 && oldpwd == NULL)
	{
		ft_putstr("bash: cd: OLDPWD not set\n", shell->err_fd);
		return (NULL);
	}
	else if (strcmp(shell->args->arg, "-") == 0 && oldpwd != NULL)
	{
		if (folder != NULL || strcmp(oldpwd, "") == 0)
		{
			ft_putstr(oldpwd, shell->out_fd);
			ft_putstr("\n", shell->out_fd);
		}
		return (oldpwd);
	}
	return (shell->args->arg);
}

char	*cd(t_minishell *shell)
{
	char	*s;
	DIR		*folder;
	char	*cwd;
	char	*oldpwd;

	cwd = (char *)malloc(PATH_MAX);
	s = ft_cases(shell, shell->oldpwd->obj2);
	if (s != NULL)
	{
		folder = opendir(s);
		chdir(s);
		if (folder == NULL)
		{
			if (shell->oldpwd->obj2
				&& strcmp((char *)shell->oldpwd->obj2, "") == 0)
				shell->oldpwd->obj2 = shell->pwd->obj2;
			else
			{
				shell->status = 10;
				ft_putstr("ayoub-shell: cd: ", shell->err_fd);
				ft_putstr(s, shell->err_fd);
				ft_putstr(": ", shell->err_fd);
				ft_putstr(strerror(errno), shell->err_fd);
				ft_putstr("\n", shell->err_fd);
			}
		}
		else
		{
			shell->oldpwd->obj2 = shell->pwd->obj2;
			getcwd(cwd, PATH_MAX);
			shell->pwd->obj2 = cwd;
		}
	}
	close(shell->out_fd);
	close(shell->in_fd);
	dup2(shell->old_stdout, 1);
	dup2(shell->old_stdin, 0);
	exit(0);
	return ("");
}
