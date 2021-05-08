#include "../includes/minishell.h"

int	is_token_material(char line)
{
	return (line == '\\' || line == '|' || line == ';');
}

int	a_token_is_set(char *c, char *line)
{
	return ((*c & SEMICOLONE_SETTER) != 0 || (*c & PIPE_SETTER) != 0
		|| redirection_is_set(c, line));
}
