#include "minishell.h"

int		bs_exists(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == BS_TOKEN)
			return (1);
		i++;
	}
	return (0);
}

char	*extract_helper(char *s, int *i, int *j, t_element *env)
{
	char		*tmp;
	t_element	*env_var;
	char		*filename;

	filename = NULL;
	if (s[*i] == BS_TOKEN || s[*i] == SQ_TOKEN || s[*i] == DQ_TOKEN)
		*i = -1;
	else
	{
		tmp = ft_substr(&s[*i - *j], 0, *j);
		env_var = catch_elem(tmp, &env);
		if (env_var && env_var->obj2)
			filename = ft_strdup(env_var->obj2);
		else
			filename = add_char_at_beginning(DOLLAR_TOKEN, tmp);
	}
	ft_free_var(s);
	ft_free_var(tmp);
	return (filename);
}

char	*file_correction(char *s, t_element *env, int err_id)
{
	int			i;
	int			j;
	t_element	*env_var;
	char		*tmp[2];
	char		*dollar;

	i = 0;
	while (s[i])
	{
		if (s[i] == BS_TOKEN || s[i] == SQ_TOKEN || s[i] == DQ_TOKEN)
		{
			j = i;
			while (s[j])
			{
				s[j] = s[j + 1];
				j++;
			}
			s[j] = '\0';
			i--;
		}
		s = dollar_case_correction(s, &i, env, err_id);
		i++;
	}
	return (s);
}

char	*extract_filename(char *s, t_element *env, int err_id)
{
	char		*filename;
	char		*tmp;
	t_element	*env_var;
	int			i;
	int			j;

	if (s[0] == DOLLAR_TOKEN && !bs_exists(s))
	{
		i = 1;
		j = 0;
		while (s[i] && s[i] != DOLLAR_TOKEN && s[i] != BS_TOKEN
			&& s[i] != SQ_TOKEN && s[i] != DQ_TOKEN && s[i] != ' ')
		{
			j++;
			i++;
		}
		return (extract_helper(s, &i, &j, env));
	}
	return (file_correction(s, env, err_id));
}
