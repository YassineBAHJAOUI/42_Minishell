/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:45:44 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 16:45:45 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*ft_lstchr(t_env *lst, const char *variable)
{
	int	len;

	if (!lst)
		return (NULL);
	len = ft_strlen(variable);
	while (lst)
	{
		if (!ft_memcmp(lst->variable, variable, len + 1) && lst->print != -2)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_env	*lst_find(t_env *lst, const char *variable)
{
	int	len;

	if (!lst)
		return (NULL);
	len = ft_strlen(variable);
	while (lst)
	{
		if (!ft_memcmp(lst->variable, variable, len + 1))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
