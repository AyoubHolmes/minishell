/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:44:16 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/04 13:46:01 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	if (n == 0)
		return ;
	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr = '\0';
		if (n)
			ptr++;
	}
}
