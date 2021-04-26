#include "minishell.h"

char	*pwd(t_minishell *shell)
{
	char	*position;

	position = malloc(PATH_MAX);
	if (getcwd(position, PATH_MAX) != NULL)
		ft_putstr(position, shell->out_fd);
	free(position);
	write(1, "\n", shell->out_fd);
	close(shell->out_fd);
	close(shell->in_fd);
	dup2(shell->old_stdout, 1);
	dup2(shell->old_stdin, 0);
	exit(0);
	return ("");
}
