#include "minishell.h"

char	*pwd(t_minishell *shell)
{
	char	*position;

	position = malloc(PATH_MAX);
	if (getcwd(position, PATH_MAX) != NULL)
		ft_putstr(position, shell->out_fd);
	ft_free_var(position);
	write(1, "\n", shell->out_fd);
	return ("");
}
