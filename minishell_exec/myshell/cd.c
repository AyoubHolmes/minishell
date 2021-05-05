#include "minishell.h"

void	error_printer(t_minishell *shell)
{
	ft_putstr("minishell: cd: ", shell->err_fd);
	ft_putstr(shell->args->arg, shell->err_fd);
	ft_putstr(": ", shell->err_fd);
	ft_putstr(strerror(errno), shell->err_fd);
	ft_putstr("\n", shell->err_fd);
	shell->er_id = 1;
}

void	edit_elem(char *elm1, char *elm2, t_element **shell_)
{
	t_element	*list;

	list = *shell_;
	if (list == NULL)
		return ;
	while (list->next)
	{
		if (ft_strcmp(list->next->obj1, elm1) == 0)
		{
			list->next->obj2 = elm2;
			return ;
		}
		list = list->next;
	}
}

char	*ft_cases(t_minishell *shell, char *oldpwd)
{
	int	dir;

	if (!shell->args || ft_strcmp(shell->args->arg, "~") == 0
		|| ft_strcmp(shell->args->arg, "~/") == 0)
		return (shell->home->obj2);
	else if (ft_strcmp(shell->args->arg, "-") == 0 && oldpwd == NULL)
	{
		ft_putstr("bash: cd: OLDPWD not set\n", shell->err_fd);
		shell->er_id = 1;
		return (NULL);
	}
	else if (ft_strcmp(shell->args->arg, "-") == 0 && oldpwd != NULL)
	{
		dir = chdir(oldpwd);
		if (dir == 0 || ft_strcmp(oldpwd, "") == 0)
		{
			ft_putstr(oldpwd, shell->out_fd);
			ft_putstr("\n", shell->out_fd);
		}
		return (oldpwd);
	}
	return (shell->args->arg);
}

void	cd_helper(t_minishell *shell, int dir, char	*cwd)
{
	if (dir == -1)
	{
		if (shell->oldpwd->obj2
			&& ft_strcmp((char *)shell->oldpwd->obj2, "") == 0)
		{
			ft_free_var(shell->oldpwd->obj2);
			shell->oldpwd->obj2 = ft_strdup(shell->pwd->obj2);
		}
		else
			error_printer(shell);
	}
	else
	{
		ft_free_var(shell->oldpwd->obj2);
		shell->oldpwd->obj2 = ft_strdup(shell->pwd->obj2);
		getcwd(cwd, PATH_MAX);
		shell->pwd->obj2 = cwd;
	}
}

char	*cd(t_minishell *shell)
{
	char	*s;
	int		dir;
	char	*cwd;
	char	*oldpwd;

	cwd = (char *)malloc(PATH_MAX);
	s = ft_cases(shell, shell->oldpwd->obj2);
	if (s != NULL)
	{
		if (shell->args)
		{
			ft_free_var(shell->args->arg);
			shell->args->arg = ft_strdup(s);
		}
		dir = chdir(s);
		cd_helper(shell, dir, cwd);
	}
	ft_free_var(cwd);
	return ("");
}
