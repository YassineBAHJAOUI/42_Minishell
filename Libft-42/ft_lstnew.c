/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:46:06 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 17:01:53 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*newenv(char *variable, char *value, int prenv)
{
	t_env	*node;

	node = malloc(sizeof (t_env));
	if (!node)
		return (NULL);
	node -> variable = variable;
	node -> value = value;
	node -> print = prenv;
	node -> next = NULL;
	return (node);
}
