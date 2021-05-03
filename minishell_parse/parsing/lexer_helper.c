#include "../../includes/minishell.h"

int	is_a_redirection(char *line)
{
	return (*line == '>' || *line == '<' || ft_strncmp(line, ">>", 2) == 0);
}

void	ft_lexer_token_helper(char *c, char *line, int setter, int token)
{
	if (token == SQ_TOKEN || token == DQ_TOKEN)
	{
		*c ^= setter;
		*c &= 4294967294;
		*c &= 4294967293;
	}
	else
		*c |= setter;
	*line = token;
	if (*line == RED3_TOKEN && *(line + 1) == '>' && *(line - 1) != RED3_TOKEN)
		*(line + 1) = RED3_TOKEN;
}

int	is_not_a_string(char c)
{
	return ((c & SINGLE_QUOTE_SETTER) == 0 && (c & DOUBLE_QUOTE_SETTER) == 0);
}

int	redirection_is_set(char *c, char *line)
{
	return (((*c & RED3_SETTER) != 0)
		|| (*c & RED1_SETTER) != 0 || (*c & RED2_SETTER) != 0 );
}
