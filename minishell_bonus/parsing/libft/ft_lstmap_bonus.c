/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:08:16 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/04 14:09:08 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*t;

	if (!lst || !f)
		return (NULL);
	p = NULL;
	while (lst != NULL)
	{
		t = ft_lstnew(f(lst->content));
		if (!t)
		{
			ft_lstclear(&p, del);
			return (NULL);
		}
		ft_lstadd_back(&p, t);
		lst = lst->next;
	}
	return (p);
}
