#include "minishell.h"

void	ft_tokenizer_2(char *c, char *line, int *escape)
{
	if (*line == '|' && is_not_a_string(*c) && *escape == 0)
		ft_lexer_token_helper(c, line, PIPE_SETTER, PIPE_TOKEN);
	else if (*line == ';' && *escape == 0 && is_not_a_string(*c))
		ft_lexer_token_helper(c, line, SEMICOLONE_SETTER, SEMICOLONE_TOKEN);
	else if (*line == '\'' && (*c & DOUBLE_QUOTE_SETTER) == 0 && *escape == 0)
		ft_lexer_token_helper(c, line, SINGLE_QUOTE_SETTER, SQ_TOKEN);
	else if (*line == '"' && *escape == 0 && (*c & SINGLE_QUOTE_SETTER) == 0)
		ft_lexer_token_helper(c, line, DOUBLE_QUOTE_SETTER, DQ_TOKEN);
	else if (((*line == '>' && *(line + 1) == '>' && is_not_a_string(*c))
			|| (*c & RED3_SETTER && *line == '>'
				&& is_not_a_string(*c)) != 0) && *escape == 0)
		ft_lexer_token_helper(c, line, RED3_SETTER, RED3_TOKEN);
	else if (*line == '>' && is_not_a_string(*c) && *escape == 0)
		ft_lexer_token_helper(c, line, RED1_SETTER, RED1_TOKEN);
	else if (*line == '<' && is_not_a_string(*c) && *escape == 0)
		ft_lexer_token_helper(c, line, RED2_SETTER, RED2_TOKEN);
	else if (*line == '$' && *escape == 0 && (is_not_a_string(*c)
			|| (*c & DOUBLE_QUOTE_SETTER) != 0)
		&& (ft_isalnum(*(line + 1)) || *(line + 1) == '?'
			|| *(line + 1) == '_'))
		ft_lexer_token_helper(c, line, DOLLAR_SETTER, DOLLAR_TOKEN);
}

void	ft_tokenizer(char *c, char *line, int *escape)
{
	ft_tokenizer_2(c, line, escape);
	if (*line == '\\' && *escape == 0 && (is_not_a_string(*c)
			|| ((*c & DOUBLE_QUOTE_SETTER) != 0 && (*(line + 1) == '`'
					|| *(line + 1) == '$' || *(line + 1) == '"'
					|| *(line + 1) == '\\'))))
	{
		*line = BS_TOKEN;
		*escape = 1;
	}
	else if (*line == '*' && *escape == 0 && is_not_a_string(*c))
		*line = STAR_TOKEN;
	else if (*escape == 1)
		*escape = 0;
	/* else if (*line == '$' && *escape == 0 && is_not_a_string(*c)
		&& (*(line + 1)== '\''|| *(line + 1)== '"'))
	{
		helper(&line);
	} */
}

int	is_token_material(char line)
{
	return (line == '\\' || line == '|' || line == ';');
}

int	a_token_is_set(char *c, char *line)
{
	return ((*c & SEMICOLONE_SETTER) != 0 || (*c & PIPE_SETTER) != 0
		|| redirection_is_set(c, line));
}

int	ft_error_checker(char *c, char *line, t_minishell *cli)
{
	cli->helper = line;
	if ((*line == '|' || *line == ';' || (*line == '\\' && *(line + 1) == '\0'))
		&& cli->is_beginning_of_line == 1 && cli->is_an_escape_character == 0)
		return (1);
	else if (((is_not_a_string(*c) && (*line == '\'' || *line == '"'))
			|| *line == '|' || *line == '\\')
		&& *(line + 1) == '\0' && cli->is_an_escape_character == 0)
		return (2);
	else if (((*c & SEMICOLONE_SETTER) != 0 || (*c & PIPE_SETTER) != 0)
		&& (*line == '|' || *line == ';')
		&& is_not_a_string(*c))
		return (3);
	else if (cli->is_an_escape_character == 0
		&& ((redirection_is_set(c, line) && is_a_redirection(line))
			|| (is_a_redirection(line)
				&& !redirection_is_set(c, line) && *(line + 1) == '\0')
			|| (*c & RED3_SETTER && *line == RED3_TOKEN
				&& *(line - 1) == RED3_TOKEN
				&& *(line + 1) == '\0')))
		return (4);
	if (a_token_is_set(c, line) && is_token_material(*line))
		return (5);
	if (ft_isalnum(*line) && is_not_a_string(*c))
		*c = 0;
	return (0);
}

void	ft_lexer_checker(char *c, char *line, t_minishell *cli)
{
	cli->status = ft_error_checker(c, line, cli);
	if (cli->status == 0)
		ft_tokenizer(c, line, &cli->is_an_escape_character);
}

void	ft_lexer(t_minishell *cli)
{
	int	i;

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
				break ;
			if (cli->is_beginning_of_line == 1)
				cli->is_beginning_of_line = 0;
			i++;
		}
		if (cli->status != 0)
			break ;
		cli->is_an_escape_character = 0;
		i++;
	}
	if (!is_not_a_string(cli->c))
		cli->status = 6;
}
