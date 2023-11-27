/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_const.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:41:00 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:41:01 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction pour créer un nouveau opérateur
t_ast	*new_oper(int type, t_ast *left, t_ast *right)
{
	t_operator	*operator;

	operator = gc(sizeof(t_operator), 1, 0);
	operator->type = type;
	operator->left = left;
	operator->right = right;
	return ((t_ast *)operator);
}

// fonction pour cree un nouveau redirection 
t_ast	*new_reder(void)
{
	t_redir	*redirection;

	redirection = gc(sizeof(t_redir), 1, 0);
	redirection->type = REDIR;
	redirection->trdr = NULL;
	redirection->fd_in = 0;
	return ((t_ast *)redirection);
}

t_ast	*new_sub(t_ast *tree)
{
	t_subsh	*sub;

	sub = gc(sizeof(t_subsh), 1, 0);
	if (!sub)
		return (NULL);
	sub->type = SUBSHELL;
	sub->sub = tree;
	return ((t_ast *)sub);
}

// fonction pour cree nouveau noeud de cmd
t_ast	*new_cmd(t_token *list)
{
	t_token		*tmp;
	t_command	*command;

	command = gc(sizeof(t_command), 1, 0);
	if (!command)
		return (NULL);
	command->type = WORD;
	command->list = list;
	tmp = list;
	while (tmp->type == WORD && tmp->type != END)
		tmp = tmp->next;
	tmp = tmp->prev;
	tmp->next = NULL;
	return ((t_ast *)command);
}
