/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:48:08 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 16:48:09 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_sp(char const *s1, char const *s2, char c)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	str = gc(ft_strlen(s1) + ft_strlen(s2) + 2, 1, 0);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = c;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		j;
	char	*str;
	int		i;

	i = -1;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	str = gc(sizeof(char) * ((ft_strlen(s1)) + ft_strlen(s2)) + 1, 1, 0);
	while (s1[++i])
		str[i] = s1[i];
	j = i;
	i = -1;
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	return (str);
}

char	*join_allo(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
		return (dup_alloc(s2));
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free((void *)s1);
	return (str);
}

char	*_strjoin(const char *s1, const char *s2)
{
	int		j;
	char	*str;
	int		i;

	i = -1;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = gc(sizeof(char) * ((ft_strlen(s1)) + ft_strlen(s2)) + 1, 1, 0);
	while (s1[++i])
		str[i] = s1[i];
	j = i;
	i = -1;
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	return (str);
}
