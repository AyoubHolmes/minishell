#include "../../includes/minishell.h"

int	ft_str(char c1, char *s)
{
	while (*s)
	{
		if (c1 == *s)
			return (1);
		s++;
	}
	return (0);
}

void	red_msg3(t_minishell *cli)
{
	if ((cli->c & RED2_SETTER) != 0 || ((cli->c & RED1_SETTER) == 0
			&& (cli->c & RED3_SETTER) == 0 && *(cli->helper) == '<'))
	{
		if (*(cli->helper) == '<' && (cli->c & RED2_SETTER) != 0)
		{
			ft_putstr("<", 2);
			if (*(cli->helper + 1) == '<')
				ft_putstr("<", 2);
			if (*(cli->helper + 2) == '<')
				ft_putstr("<", 2);
		}
		else if (*cli->helper == '>')
		{
			ft_putstr(">", 2);
			if (*(cli->helper + 1) == '>')
				ft_putstr(">", 2);
		}
		else
			ft_putstr("newline", 2);
	}
}

void	red_msg2(t_minishell *cli)
{
	if ((cli->c & RED1_SETTER) != 0 || ((cli->c & RED2_SETTER) == 0
			&& (cli->c & RED3_SETTER) == 0 && *(cli->helper) == '>'))
	{
		if (*(cli->helper) == '>' && (cli->c & RED1_SETTER) != 0)
		{
			ft_putstr(">", 2);
			if (*(cli->helper + 1) == '>')
				ft_putstr(">", 2);
		}
		else if (*cli->helper == '<')
		{
			ft_putstr("<", 2);
			if (*(cli->helper + 1) == '<')
				ft_putstr("<", 2);
			if (*(cli->helper + 2) == '<')
				ft_putstr("<", 2);
		}
		else
			ft_putstr("newline", 2);
	}
}

void	red_msg(t_minishell *cli)
{
	red_msg2(cli);
	red_msg3(cli);
	if ((cli->c & RED3_SETTER) != 0)
	{
		if (*(cli->helper) == '>')
		{
			ft_putstr(">", 2);
			if (*(cli->helper + 1) == '>')
				ft_putstr(">", 2);
		}
		else if (*(cli->helper) == '<')
		{
			ft_putstr("<", 2);
			if (*(cli->helper + 1) == '<')
				ft_putstr("<", 2);
		}
		else
			ft_putstr("newline", 2);
	}
}

void	lexer_debugger(t_minishell *cli)
{
	char	c;

	if (cli->status != 0)
	{
		ft_putstr("cool-shell: ", 2);
		if (!ft_str(*cli->helper, "\\\"'"))
		{
			ft_putstr("syntax error near unexpected token `", 2);
			if (*cli->helper == ';' || *cli->helper == '|')
			{
				write(2, cli->helper, 1);
				if (*(cli->helper + 1) == *(cli->helper)
					|| (*(cli->helper) == ';'
						&& *(cli->helper - 1) == SEMICOLONE_TOKEN))
					write(2, cli->helper, 1);
			}
			else if (cli->status == 4)
				red_msg(cli);
			ft_putstr("'\n", 2);
		}
		else
			ft_putstr("multi-line commands are not allowed.\n", 2);
		cli->error_id = 258;
	}
}
