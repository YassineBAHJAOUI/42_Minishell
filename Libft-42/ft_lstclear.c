/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:45:51 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 16:45:52 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_env **lst)
{
	t_env	*c;

	if (!lst)
		return ;
	c = *lst;
	while (c)
	{
		if (c->next == NULL)
			break ;
		c = c->next;
		free(*lst);
		*lst = c;
	}
	free(*lst);
	*lst = NULL;
}

void	delete_node(t_env **head, char *var)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *head;
	while (current != NULL && ft_memcmp(current->variable, var, ft_strlen(var)
			+ 1))
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	if (prev == NULL)
		*head = current->next;
	else
		prev->next = current->next;
	free(current->variable);
	free(current->value);
	free(current);
	current = NULL;
}
