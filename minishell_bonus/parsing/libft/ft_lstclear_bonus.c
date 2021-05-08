/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:17:47 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/04 14:10:08 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *t))
{
	t_list	*p;
	t_list	*q;

	if (*lst != NULL && del)
	{
		p = *lst;
		while (p != NULL)
		{
			q = p;
			p = p->next;
			del(q->content);
			free(q);
		}
		*lst = NULL;
	}
}
