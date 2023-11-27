/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:36:30 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:36:44 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

// créer un nouveau jeton (`t_token`) avec les paramètres spécifiés.
t_token	*ft_newtoken(t_flag type, char *word, int flag, int hdoc)
{
	t_token	*token;

	token = gc(sizeof(t_token), 1, 0);
	token->token = word;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	token->down = NULL;
	token->expand = false;
	token->hdoc = false;
	(flag) && (token->expand = true);
	(hdoc) && (token->hdoc = true);
	return (token);
}

// obtenir le dernier jeton dans une liste de jetons (t_token).
t_token	*lasttok(t_token *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

// ajouter un nouveau jeton (new) à la fin d'une liste de jetons (lst).
void	addtok(t_token **lst, t_token *new)
{
	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->prev = lasttok(*lst);
	lasttok(*lst)->next = new;
	new->next = NULL;
}

// fonction recherche le dernier token descendant
t_token	*lasttok_down(t_token *lst)
{
	while (lst)
	{
		if (lst->down == NULL)
			break ;
		lst = lst->down;
	}
	return (lst);
}

// taille de token
int	size_token(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
