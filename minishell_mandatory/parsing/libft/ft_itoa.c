/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikma <shikma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:10:10 by aboulbaz          #+#    #+#             */
/*   Updated: 2021/05/05 11:08:35 by shikma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_int(int n)
{
	int	i;
	int	temp;

	temp = n;
	i = 0;
	while (temp != 0)
	{
		temp /= 10;
		i++;
	}
	return (i);
}

char	ft_helper(int nb)
{
	if (nb == 0)
		return ('0');
	return ('-');
}

char	*ft_helper2(char **nbr, int i)
{
	*nbr = (char *)malloc(i);
	return (*nbr);
}

char	*ft_itoa(int nb)
{
	int		i;
	char	*nbr;

	i = size_int(nb);
	if (nb <= 0)
	{
		if (!ft_helper2(&nbr, 2 + i++))
			return (0);
		nbr[0] = ft_helper(nb);
		if (nb == -2147483648)
			return (ft_strdup("-2147483648"));
		else
			nb = nb * -1;
	}
	else if (!ft_helper2(&nbr, i + 1))
		return (0);
	nbr[i] = 0;
	while (nb != 0)
	{
		i--;
		nbr[i] = 48 + (nb % 10);
		nb = nb / 10;
	}
	return (nbr);
}
