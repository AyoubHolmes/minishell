/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:12:16 by shikma            #+#    #+#             */
/*   Updated: 2021/05/01 08:56:16 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char		*string2;
// 	size_t		j;

// 	j = 0;
// 	if (!s)
// 		return (ft_strdup(""));
// 	if (ft_strlen(s) < start)
// 		return (ft_strdup(""));
// 	string2 = (char*)malloc((len + 1) * sizeof(char));
// 	if (string2 == NULL)
// 		return (NULL);
// 	j = 0;
// 	while (s[start + j] && j < len)
// 	{
// 		string2[j] = (char)s[start + j];
// 		j++;
// 	}
// 	string2[j] = '\0';
// 	free(s);
// 	return (string2);
// }

char	*ft_strjoin(char *s1, char *s2)
{
	char				*s3;
	char				*str1;
	char				*str2;
	unsigned int		len;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	str1 = (char *)s1;
	str2 = (char *)s2;
	len = 0;
	s3 = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (s3 == NULL)
		return (NULL);
	while (*str1)
		s3[len++] = *(str1++);
	while (*str2)
		s3[len++] = *(str2++);
	// free(s1);
	// free(s2);
	s3[len] = '\0';
	return (s3);
}

char	*ft_strchr(const char *s, int c)
{
	char	conv;
	int		i;

	i = 0;
	conv = c;
	while (s[i] && s[i] != conv)
		i++;
	if (s[i] == conv)
		return ((char *)&s[i]);
	else
		return (0);
}

int		valid_or_not(char c, int id)
{
	if(id == 1 && c == '=')
		return(0);
	if (ft_isalnum(c) == 1 || c == '_')
		return (0);
	return (1);
}

int	check_identifier(char *str, t_minishell *shell, int id)
{
	int	i;

	i = 0;
	while (str[i] || ft_strcmp(str, "\0") == 0)
	{
		ft_putnbr_fd(valid_or_not(str[i],id),1);
		ft_putstr_parse("\n");
		if(ft_strcmp(str, "\0") == 0 || str[0] == '=' || ft_isdigit(str[0]) == 1 || valid_or_not(str[i],id) == 1)
		{
			ft_putstr("ayoub-shell:", shell->err_fd);
			ft_putstr(shell->cmd, shell->err_fd);
			ft_putstr(": `", shell->err_fd);
			ft_putstr(str, shell->err_fd);
			ft_putstr("': not a valid identifier\n", shell->err_fd);
			shell->status = 1;
			return (0);
		}
		i++;
	}
	return(1);
}