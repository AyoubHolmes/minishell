/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:03:52 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/04 13:57:08 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t n)
{
	char	*dst;
	size_t	i;
	size_t	len;

	i = 0;
	if (!src)
		return (NULL);
	if (start > ft_strlen(src))
		return (ft_strdup(""));
	len = ft_strlen(src + start);
	if (n > len)
		n = len;
	dst = (char *)malloc(sizeof(char) * n + 1);
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, src + start, n);
	dst[n] = '\0';
	return (dst);
}
