/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:47:46 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 16:53:14 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	if (!s)
		return (NULL);
	while (*(s + (++i)))
		if (*(s + i) == (unsigned char)c)
			return ((char *)s + i);
	if (*(s + i) == (unsigned char)c)
		return ((char *)s + i);
	return (NULL);
}
