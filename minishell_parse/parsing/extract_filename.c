#include "../../includes/minishell.h"

char	*extract_helper(char *s, int *i, int *j, t_element *env)
{
	char	*tmp;
	t_element	*env_var;
	char *filename;

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
	return (filename);
}

char	*extract_filename(char *s, t_element *env, int err_id)
{
	char *filename;
	char *tmp;
	t_element *env_var;
	int i;
	int j;

	if (s[0] == DOLLAR_TOKEN)
	{
		i = 1;
		j = 0;
		while(s[i] && s[i] != DOLLAR_TOKEN && s[i] != BS_TOKEN &&
			s[i] != SQ_TOKEN && s[i] != DQ_TOKEN && s[i] != ' ')
		{
			j++;
			i++;
		}
		filename = extract_helper(s, &i, &j, env);
	}
	else if (i == -1 || 1)
		filename = arg_correction(s, env, err_id);
	return (filename);
}