#include "../../includes/minishell.h"

int     is_a_quotation(char *line)
{
	return (*line == '\'' || *line == '"');
}

int     is_a_redirection(char *line)
{
	return (*line == '>' || *line == '<' || ft_strncmp(line, ">>", 2) == 0);
}

int     is_a_separatore(char *line)
{
	return (*line == '|' || *line == ';');
}

int     is_a_dollar(char c)
{
	return (c == '$');
}

int     is_an_escape_char(char c)
{
	return (c == '\\');
}

int     is_alphanum(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||\
		(c >= 'A' && c <= 'Z'));
}

void    ft_lexer_token_helper(char *c, char *line, int setter, int token)
{
	if (token == SINGLE_QUOTE_TOKEN || token == DOUBLE_QUOTE_TOKEN)
	{
		*c ^= setter;
		*c &= 4294967294;
		*c &= 4294967293;
	}
	else
		*c |= setter;
	*line = token;
	if (*line == RED3_TOKEN && *(line + 1) == '>' && *(line - 1) != RED3_TOKEN )
	{
		//line += 1;
		*(line + 1) = RED3_TOKEN;
	}
}

int     is_not_a_string(char c)
{
	return((c & SINGLE_QUOTE_SETTER) == 0 && (c & DOUBLE_QUOTE_SETTER) == 0);
}

int     seperator_is_set(char c)
{
	return((c & SEMICOLONE_SETTER) != 0 || (c & PIPE_SETTER) != 0);
}

int     redirection_is_set(char *c, char *line)
{
	return(((*c & RED3_SETTER) != 0) ||\
		(*c & RED1_SETTER) != 0 || (*c & RED2_SETTER) != 0 );
}

int     is_first_quotation(char c, char *line)
{
	return (is_not_a_string(c) && is_a_quotation(line));
}

void    ft_tokenizer(char *c, char *line, int *escape)
{
	if (*line == '|' && is_not_a_string(*c) && *escape == 0)
		ft_lexer_token_helper(c, line, PIPE_SETTER, PIPE_TOKEN);
	else if (*line == ';' && *escape == 0 && is_not_a_string(*c))
		ft_lexer_token_helper(c, line, SEMICOLONE_SETTER, SEMICOLONE_TOKEN);
	else if (*line == '\'' && (*c & DOUBLE_QUOTE_SETTER) == 0 && *escape == 0)
		ft_lexer_token_helper(c, line, SINGLE_QUOTE_SETTER, SINGLE_QUOTE_TOKEN);
	else if (*line == '"' && *escape == 0 && (*c & SINGLE_QUOTE_SETTER) == 0)
		ft_lexer_token_helper(c, line, DOUBLE_QUOTE_SETTER, DOUBLE_QUOTE_TOKEN);
	else if (((*line == '>' && *(line + 1) == '>' && is_not_a_string(*c))\
		|| (*c & RED3_SETTER && *line == '>' && is_not_a_string(*c)) != 0) && *escape == 0)
		ft_lexer_token_helper(c, line, RED3_SETTER, RED3_TOKEN);
	else if (*line == '>' && is_not_a_string(*c) && *escape == 0)
		ft_lexer_token_helper(c, line, RED1_SETTER, RED1_TOKEN);
	else if (*line == '<' && is_not_a_string(*c) && *escape == 0)
		ft_lexer_token_helper(c, line, RED2_SETTER, RED2_TOKEN);
	else if (*line == '$' && *escape == 0 && (is_not_a_string(*c) ||\
		(*c & DOUBLE_QUOTE_SETTER) != 0) && (is_alphanum(*(line + 1)) || *(line + 1) == '?'\
		|| *(line + 1) == '_'))
		ft_lexer_token_helper(c, line, DOLLAR_SETTER, DOLLAR_TOKEN);
	else if (*line == '\\' && *escape == 0 && (is_not_a_string(*c) ||\
		((*c & DOUBLE_QUOTE_SETTER) != 0 && (*(line + 1) == '`' || *(line + 1) == '$' || *(line + 1) == '"' || *(line + 1) == '\\'))))
	{
		*line = BACKSLASH_TOKEN;
		*escape = 1;
	}
	else if (*escape == 1)
		*escape = 0;
}

int    ft_error_checker(char *c, char *line, t_minishell *cli)
{
	cli->helper = line;
	if ((*line == '|' || *line == ';' || (*line == '\\' && *(line + 1) == '\0'))\
		&& cli->is_beginning_of_line == 1 && cli->is_an_escape_character == 0)
		return (1);
	else if ((is_first_quotation(*c, line)\
	|| *line == '|' || *line == '\\')\
	&& *(line + 1) == '\0' && cli->is_an_escape_character == 0)
		return (2);
	else if (seperator_is_set(*c) && is_a_separatore(line)\
		&& is_not_a_string(*c))
		return (3);
	else if (cli->is_an_escape_character == 0 && ((redirection_is_set(c, line) && is_a_redirection(line)) ||\
		(is_a_redirection(line) && !redirection_is_set(c, line) && *(line + 1) == '\0') ||\
		(*c & RED3_SETTER && *line == RED3_TOKEN && *(line - 1) == RED3_TOKEN && *(line + 1) == '\0')))
		return (4);
	if (is_alphanum(*line) && is_not_a_string(*c))
		*c = 0;
	return (0);
}

void    ft_lexer_checker(char *c, char *line, t_minishell *cli)
{
	cli->status = ft_error_checker(c, line, cli);
	if (cli->status == 0)
		ft_tokenizer(c, line, &cli->is_an_escape_character);
}

void    ft_lexer(t_minishell *cli)
{
	int i;

	cli->c = 0;
	i = 0;
	cli->is_beginning_of_line = 1;
	cli->is_an_escape_character = 0;
	while (cli->line[i])
	{
		while (cli->line[i] && cli->line[i] != ' ')
		{
			ft_lexer_checker(&cli->c, &cli->line[i], cli);
			if (cli->status != 0)
				break;
			if (cli->is_beginning_of_line == 1)
				cli->is_beginning_of_line = 0;
			i++;
		}
		if (cli->status != 0)
			break;
		cli->is_an_escape_character = 0;
		i++;
	}
	if (!is_not_a_string(cli->c))
		cli->status = 2;
}
