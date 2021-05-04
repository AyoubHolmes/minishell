#include "../../includes/minishell.h"

void	dollar_traversal(char *s, int *i, int *j)
{
	while (s[*i] && s[*i] != DOLLAR_TOKEN && s[*i] != BS_TOKEN
		&& s[*i] != SQ_TOKEN
		&& s[*i] != DQ_TOKEN && s[*i] != ' ')
	{
		(*j)++;
		(*i)++;
	}
}

char	*error_var(char *s, int *i, int *j, int err_id)
{
	char	*dollar;

	if (s[*i] == '?')
		dollar = ft_itoa(err_id);
	else
		dollar = ft_strdup("");
	(*i)++;
	(*j)++;
	return (dollar);
}

void	dollar_case_correction(char *s, int *i, t_element *env, int err_id)
{
	int			j;
	char		*tmp[2];
	t_element	*env_var;
	char		*dollar;

	dollar = "";
	if (s[*i] == DOLLAR_TOKEN)
	{
		(*i)++;
		j = 0;
		if (ft_isalnum(s[*i]))
		{
			dollar_traversal(s, i, &j);
			tmp[0] = ft_substr(&s[(*i) - j], 0, j);
			env_var = catch_elem(tmp[0], &env);
			if (env_var && env_var->obj2)
				dollar = ft_strdup(env_var->obj2);
		}
		else
			dollar = error_var(s, i, &j, err_id);
		tmp[0] = ft_strjoin(ft_substr(s, 0, (*i) - j - 1), dollar);
		tmp[1] = s;
		s = ft_strjoin(tmp[0], ft_substr(&s[*i], 0, ft_strlen(s) - (*i)));
		*i = (*i - j) + ft_strlen(dollar) - 2;
	}
}

char	*arg_correction(char *s, t_element *env, int err_id)
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
			i--;
		}
		dollar_case_correction(s, &i, env, err_id);
		i++;
	}
	return (s);
}
