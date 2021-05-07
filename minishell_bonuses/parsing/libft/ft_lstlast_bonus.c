/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:18:46 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/04 14:09:35 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*t;

	if (lst)
	{
		t = lst;
		while (t->next != NULL)
		{
			t = t->next;
		}
		return (t);
	}
	return (NULL);
}
