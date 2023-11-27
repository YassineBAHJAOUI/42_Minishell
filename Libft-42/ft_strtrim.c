/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:48:52 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 16:48:54 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	len;

	if (!s1 || !set)
		return (NULL);
	i = -1;
	len = ft_strlen(s1);
	while (s1[++i])
		if (!ft_strchr(set, s1[i]))
			break ;
	while (--len)
		if (!ft_strchr(set, s1[len]))
			break ;
	return (ft_substr(s1, i, (len + 1) - i));
}

char	*trim_allo(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	int			len;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	start = s1;
	end = s1 + len - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	if (start == s1 + len)
		return (dup_alloc(""));
	while (*end && ft_strchr(set, *end))
		end--;
	return (sub_malloc(start, 0, end - start + 1));
}
