/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:18:24 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/04 14:10:15 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*p;

	if (*alst == NULL)
		*alst = new;
	else
	{
		p = *alst;
		if (new)
		{
			while (p->next != NULL)
				p = p->next;
			p->next = new;
			new->next = NULL;
		}
	}
}
