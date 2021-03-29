#include "minishell.h"

// ---------------------------- DEFINING THE TOKENS ------------------------

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

// --------------------------------------------------------------



void    ft_lexer_token_helper(char *c, char *line, int setter, int token)
{
	if (token == SINGLE_QUOTE_TOKEN || token == DOUBLE_QUOTE_TOKEN)
		*c ^= setter;
	else
		*c |= setter;
	*line = token;
}
// ------------------------ Checking functions ----------------------
int     is_not_a_string(char c)
{
	return((c & SINGLE_QUOTE_SETTER) == 0 && (c & DOUBLE_QUOTE_SETTER) == 0);
}

int     seperator_is_set(char c)
{
	return((c & SEMICOLONE_SETTER) != 0 || (c & PIPE_SETTER) != 0);
}

int     is_first_quotation(char c, char *line)
{
	return (is_not_a_string(c) && is_a_quotation(line));
}

// -----------------------TOKENIZER ------------------------------------
void    ft_tokenizer(char *c, char *line, int *escape)
{
	if (*line == '|' && is_not_a_string(*c))
		ft_lexer_token_helper(c, line, PIPE_SETTER, PIPE_TOKEN);
	else if (*line == ';' && is_not_a_string(*c))
		ft_lexer_token_helper(c, line, SEMICOLONE_SETTER, SEMICOLONE_TOKEN);
	else if (*line == '\'' && (*c & DOUBLE_QUOTE_SETTER) == 0)
		ft_lexer_token_helper(c, line, SINGLE_QUOTE_SETTER, SINGLE_QUOTE_TOKEN);
	else if (*line == '"' && *escape == 0 && (*c & SINGLE_QUOTE_SETTER) == 0)
		ft_lexer_token_helper(c, line, DOUBLE_QUOTE_SETTER, DOUBLE_QUOTE_TOKEN);
	else if (*line == '>' && is_not_a_string(*c))
		ft_lexer_token_helper(c, line, REDIRECTION1_SETTER, REDIRECTION1_TOKEN);
	else if (*line == '<' && is_not_a_string(*c))
		ft_lexer_token_helper(c, line, REDIRECTION2_SETTER, REDIRECTION2_TOKEN);
	else if (ft_strncmp(line, ">>", 2) == 0 && is_not_a_string(*c))
		ft_lexer_token_helper(c, line, REDIRECTION3_SETTER, REDIRECTION3_TOKEN);
	else if (*line == '$' && *escape == 0 && (is_not_a_string(*c) ||\
		(*c & DOUBLE_QUOTE_SETTER) != 0) && is_alphanum(*(line + 1)))
		ft_lexer_token_helper(c, line, DOLLAR_SETTER, DOLLAR_TOKEN);
	else if (*line == '\\' && *escape == 0 && (is_not_a_string(*c) ||\
		((*c & DOUBLE_QUOTE_SETTER) != 0 && (*(line + 1) == '`' || *(line + 1) == '$' || *(line + 1) == '"'))))
	{
		*line = BACKSLASH_TOKEN;
		*escape = 1;
	}
}
// -----------------------ERROR HANDLERS ------------------------------------

int     redirection_operator(char c)
{
	return((c & REDIRECTION1_TOKEN) != 0 || (c & REDIRECTION2_TOKEN) != 0 ||\
		   (c & REDIRECTION3_TOKEN) != 0);
}

int    ft_error_checker(char *c, char *line, t_minishell *cli)
{
	if ((*line == '|' || *line == ';' || *line == '\\')\
		&& cli->is_beginning_of_line == 1)
		return (1);
	if ((is_a_redirection(line) || is_first_quotation(*c, line) || *line == '|' )\
		&& *(line + 1) == '\0')
		return (2);
	if (seperator_is_set(*c) && is_a_separatore(line) && is_not_a_string(*c))
		return (3);
	if (is_alphanum(*line) && is_not_a_string(*c) && !redirection_operator(*c))
	{
		cli->is_an_escape_character = 0;
		*c = 0;
	}
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
		if (cli->line[i] != ' ')
		{
			ft_lexer_checker(&cli->c, &cli->line[i], cli);
			if (cli->status != 0)
				break;
			if (cli->is_beginning_of_line == 1)
				cli->is_beginning_of_line = 0;
		}
		i++;
	}
	if (!is_not_a_string(cli->c))
		cli->status = 4;
}

void    lexer_debugger(t_minishell *cli)
{
	ft_putstr_parse("Line After Lexer: ");
	ft_putstr_parse(cli->line);
	ft_putstr_parse("\n");
	ft_putnbr_fd(cli->status, 1);
	ft_putstr_parse("\n");
}