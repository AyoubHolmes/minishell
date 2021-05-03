/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:54:14 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/03 12:21:33 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	exists(char c, const char *set)
{
	size_t i;

	i = 0;
	if (set)
	{
		while (set[i])
		{
			if (c == set[i++])
				return (1);
		}
	}
	return (0);
}

static size_t	first_str(const char *s, const char *set)
{
	size_t i;

	i = 0;
	if (s && set)
	{
		while (exists(s[i], set))
			i++;
		return (i);
	}
	return (0);
}

static size_t	last_str(const char *s, const char *set, size_t lens)
{
	size_t i;

	i = 0;
	if (s && set && lens > 0)
	{
		while (exists(s[lens - i - 1], set))
			i++;
		return (i);
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int len;
	int start;

	if (!set || !s1)
		return (NULL);
	if (s1[first_str(s1, set)] == '\0')
		return (ft_strdup(""));
	start = first_str(s1, set);
	len = ft_strlen(s1 + start) - last_str(s1, set, ft_strlen(s1));
	return (ft_substr(s1, start, len));
}

char	*ft_trim_end(char const *s1,char const *end)
{
	int j;
	int i;

	i = 0;
	j = 0;
	if (!end || !s1)
		return (NULL);
	while (s1[i] !='\0')
	{
		if (s1[i] == end[j] && end[j] !='\0')
		{
			j++;
			if (j == ft_strlen(end) && s1[i + 1] == '\0')
				return (ft_substr(s1,0, i + 1- j));
		}
		else
			j = 0;
		i++;
	}
	return (ft_strdup("."));
}