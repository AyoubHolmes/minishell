#include "minishell.h"

void	error_printer(t_minishell *shell)
{
	shell->status = 10;
	ft_putstr("ayoub-shell: cd: ", shell->err_fd);
	ft_putstr(shell->simple_cmd->args->arg, shell->err_fd);
	ft_putstr(": ", shell->err_fd);
	ft_putstr(strerror(errno), shell->err_fd);
	ft_putstr("\n", shell->err_fd);
	shell->status = 1;
}

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

	if (!shell->args || strcmp(shell->args->arg, "~") == 0
		|| strcmp(shell->args->arg, "~/") == 0)
		return (shell->home->obj2);
	else if (strcmp(shell->args->arg, "-") == 0 && oldpwd == NULL)
	{
		ft_putstr("bash: cd: OLDPWD not set\n", shell->err_fd);
		shell->status = 1;
		return (NULL);
	}
	else if (strcmp(shell->args->arg, "-") == 0 && oldpwd != NULL)
	{
		folder = opendir(oldpwd);
		if (folder != NULL || strcmp(oldpwd, "") == 0)
		{
			ft_putstr(oldpwd, shell->out_fd);
			ft_putstr("\n", shell->out_fd);
		}
		free(folder);
		folder = NULL;
		return (oldpwd);
	}
	return (shell->args->arg);
}

void	cd_helper(t_minishell *shell, DIR *folder, char	*cwd)
{
	if (folder == NULL)
	{
		if (shell->oldpwd->obj2
			&& strcmp((char *)shell->oldpwd->obj2, "") == 0)
			shell->oldpwd->obj2 = shell->pwd->obj2;
		else
			error_printer(shell);
	}
	else
	{
		shell->oldpwd->obj2 = shell->pwd->obj2;
		getcwd(cwd, PATH_MAX);
		shell->pwd->obj2 = cwd;
	}
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
		cd_helper(shell, folder, cwd);
	}
	free(cwd);
	cwd = NULL;
	return ("");
}
