#include "../../includes/minishell.h"

char	*add_char_at_beginning(char c, char *s)
{
	int		i;
	char	*t;

	t = malloc(ft_strlen(s) + 2);
	t[0] = c;
	i = 0;
	while (s[i])
	{
		t[i + 1] = s[i];
		i++;
	}
	t[i + 1] = '\0';
	return (t);
}

void	traversal_fd(int *i, char *cmd, int *size)
{
	(*i)++;
	if (cmd[*i] == RED3_TOKEN)
		(*i)++;
	while (cmd[*i] && cmd[*i] == ' ')
		(*i)++;
	*size = 0;
	while (cmd[*i] && cmd[*i] != ' ' && !is_a_redirection_token(&cmd[*i]))
	{
		if (cmd[*i] == SQ_TOKEN || cmd[*i] == DQ_TOKEN)
		{
			(*size)++;
			(*i)++;
			while (cmd[*i] && (cmd[*i] != SQ_TOKEN && cmd[*i] != DQ_TOKEN))
			{
				(*size)++;
				(*i)++;
			}
		}
		(*size)++;
		(*i)++;
	}
}

int	error_fd(char *filename, t_simple_cmd **s)
{
	if (errno != 0 || filename[0] == DOLLAR_TOKEN)
	{
		if (!(*s)->cmd)
			ft_putstr("minishell", 2);
		else
			ft_putstr((*s)->cmd, 2);
		ft_putstr(": ", 2);
		if (filename[0] == DOLLAR_TOKEN)
			ft_putstr_fd("$", 2);
		else
			write(2, &filename[0], 1);
		ft_putstr(&filename[1], 2);
		ft_putstr(": ", 2);
		if (errno != 0)
			ft_putstr(strerror(errno), 2);
		else
			ft_putstr_fd("ambiguous redirect", 2);
		ft_putstr("\n", 2);
		return (1);
	}
	ft_free_var(filename);
	return (0);
}

int	get_fd_file(char *cmd, int *i, t_simple_cmd **s, t_element *env)
{
	int		start;
	int		size;
	char	*filename;
	char	redirect;

	redirect = cmd[*i];
	errno = 0;
	traversal_fd(i, cmd, &size);
	filename = extract_filename(ft_substr(&cmd[(*i) - size], 0, size),
			env, (*s)->err_id);
	if (redirect == RED1_TOKEN && filename[0] != DOLLAR_TOKEN)
		(*s)->out_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (redirect == RED2_TOKEN && filename[0] != DOLLAR_TOKEN)
		(*s)->in_fd = open(filename, O_RDONLY, 0666);
	else if (redirect == RED3_TOKEN && filename[0] != DOLLAR_TOKEN)
		(*s)->out_fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
	return (error_fd(filename, s));
}
