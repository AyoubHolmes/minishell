#include "minishell.h"

int	ft_str(char c1, char *s)
{
	while(*s)
	{
		if (c1 == *s)
			return (1);
		s++;
	}
	return (0);
}

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
	{
		*c ^= setter;
		*c &= 4294967294;
		*c &= 4294967293;
	}
	else
		*c |= setter;
	*line = token;
	if (*line == REDIRECTION3_TOKEN && *(line + 1) == '>' && *(line - 1) != REDIRECTION3_TOKEN )
	{
		//line += 1;
		*(line + 1) = REDIRECTION3_TOKEN;
	}
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

int     redirection_is_set(char *c, char *line)
{
	return(((*c & REDIRECTION3_SETTER) != 0) ||\
		(*c & REDIRECTION1_SETTER) != 0 || (*c & REDIRECTION2_SETTER) != 0 );
}

int     is_first_quotation(char c, char *line)
{
	return (is_not_a_string(c) && is_a_quotation(line));
}

// -----------------------TOKENIZER ------------------------------------

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
		|| (*c & REDIRECTION3_SETTER && *line == '>' && is_not_a_string(*c)) != 0) && *escape == 0)
		ft_lexer_token_helper(c, line, REDIRECTION3_SETTER, REDIRECTION3_TOKEN);
	else if (*line == '>' && is_not_a_string(*c) && *escape == 0)
		ft_lexer_token_helper(c, line, REDIRECTION1_SETTER, REDIRECTION1_TOKEN);
	else if (*line == '<' && is_not_a_string(*c) && *escape == 0)
		ft_lexer_token_helper(c, line, REDIRECTION2_SETTER, REDIRECTION2_TOKEN);
	else if (*line == '$' && *escape == 0 && (is_not_a_string(*c) ||\
		(*c & DOUBLE_QUOTE_SETTER) != 0) && is_alphanum(*(line + 1)))
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
		(*c & REDIRECTION3_SETTER && *line == REDIRECTION3_TOKEN && *(line - 1) == REDIRECTION3_TOKEN && *(line + 1) == '\0')))
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
		cli->status = 5;
}

void	redirection_error_messages(t_minishell *cli)
{
	if ((cli->c & REDIRECTION1_SETTER) != 0 ||((cli->c & REDIRECTION2_SETTER) == 0 && (cli->c & REDIRECTION3_SETTER) == 0 && *(cli->helper) == '>'))
	{
		if (*(cli->helper) == '>' && (cli->c & REDIRECTION1_SETTER) != 0)
		{
			ft_putstr(">", 2);
			if( *(cli->helper + 1) == '>')
				ft_putstr(">", 2);
		}
		else if (*cli->helper == '<')
		{
			ft_putstr("<", 2);
			if( *(cli->helper + 1) == '<')
				ft_putstr("<", 2);
			if( *(cli->helper + 2) == '<')
				ft_putstr("<", 2);
		}
		else
			ft_putstr("newline", 2);
	}
	else if ((cli->c & REDIRECTION2_SETTER) != 0 || ((cli->c & REDIRECTION1_SETTER) == 0 && (cli->c & REDIRECTION3_SETTER) == 0 && *(cli->helper) == '<'))
	{
		if (*(cli->helper) == '<' && (cli->c & REDIRECTION2_SETTER) != 0)
		{
			ft_putstr("<", 2);
			if( *(cli->helper + 1) == '<')
				ft_putstr("<", 2);
			if( *(cli->helper + 2) == '<')
				ft_putstr("<", 2);
		}
		else if (*cli->helper == '>')
		{
			ft_putstr(">", 2);
			if( *(cli->helper + 1) == '>')
				ft_putstr(">", 2);
		}
		else
			ft_putstr("newline", 2);
	}
	if ((cli->c & REDIRECTION3_SETTER) != 0)
	{
		if (*(cli->helper) == '>')
		{
			ft_putstr(">", 2);
			if( *(cli->helper + 1) == '>')
				ft_putstr(">", 2);
		}
		else if (*(cli->helper) == '<')
		{
			ft_putstr("<", 2);
			if( *(cli->helper + 1) == '<')
				ft_putstr("<", 2);
		}
		else
			ft_putstr("newline", 2);
	}
}

void    lexer_debugger(t_minishell *cli)
{
	char c;

	/* ft_putstr_parse("Line After Lexer: ");
	ft_putstr_parse(cli->line);
	ft_putstr_parse("\n");
	if (cli->status != 0)
	{
		ft_putstr_parse("Line Helper: ");
		ft_putstr_parse(cli->helper);
		ft_putstr_parse("\n");
		ft_putstr_parse("Error ID: ");
		ft_putnbr_fd(cli->status, 1);
		ft_putstr_parse("\n");
	} */
	if (cli->status != 0)
	{
		ft_putstr("cool-shell: ", 2);
		if (!ft_str(*cli->helper, "\\\"'"))
		{
			ft_putstr("syntax error near unexpected token `", 2);
			if (*cli->helper == ';' || *cli->helper == '|')
			{
				write(2, cli->helper, 1);
				if (*(cli->helper + 1) == *(cli->helper) ||\
				(*(cli->helper) == ';' &&  *(cli->helper - 1) == SEMICOLONE_TOKEN))
					write(2, cli->helper, 1);
			}
			else if (cli->status == 4)
				redirection_error_messages(cli);
			ft_putstr("'\n", 2);
		}
		else
			ft_putstr("multi-line commands are not allowed.\n", 2);
	}
}