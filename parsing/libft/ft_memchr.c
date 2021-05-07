/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:40:02 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/04 13:49:04 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*src;

	src = (char *)s;
	while (n-- > 0)
	{
		if (*src != c)
			src++;
		else
			return (src);
	}
	return (NULL);
}
