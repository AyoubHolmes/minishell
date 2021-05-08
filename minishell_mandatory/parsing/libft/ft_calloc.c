/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 21:02:03 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/04 13:47:12 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*s;

	s = (unsigned char *)malloc(size * count);
	if (!s)
		return (NULL);
	ft_bzero(s, size * count);
	return ((void *)s);
}
