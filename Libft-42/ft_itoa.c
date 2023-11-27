/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:45:21 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 16:45:22 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count++;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	nb;
	char		*str;

	if (n == 0)
		return (ft_strdup("0"));
	i = count(n);
	nb = n;
	str = gc(sizeof(char) * (i + 1), 1, 0);
	str[i] = '\0';
	if (n < 0)
		nb = nb * (-1);
	while (--i >= 0)
	{
		str[i] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*itoa_allo(int n)
{
	int			i;
	long int	nb;
	char		*str;

	if (n == 0)
		return (dup_alloc("0"));
	i = count(n);
	nb = n;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (str);
	str[i] = '\0';
	if (n < 0)
		nb = nb * (-1);
	while (--i >= 0)
	{
		str[i] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
