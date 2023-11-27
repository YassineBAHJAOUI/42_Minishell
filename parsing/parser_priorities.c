/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_priorities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:43:03 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:43:04 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fonction déterminer s'il s'agit d'une commande et si c'est le cas,
// il crée un nœud de commande
t_ast	*parse_cmd(t_token **tok)
{
	t_ast	*ast;
	t_token	*tmp;

	if ((*tok)->type == OPAR)
		return (parse_sub(tok));
	if ((*tok)->type == WORD)
	{
		tmp = *tok;
		while ((*tok)->type == WORD && (*tok)->type != END)
			*tok = (*tok)->next;
		return (ast = new_cmd(tmp), ast);
	}
	return (NULL);
}

/* fonction pour analyser une commande potentiellement 
     suivie de redirections (RIN, ROUT, HEREDOC, APPEND) 
       s'il s'agit d'une redirection en appel la fonction redire_info */
t_ast	*parse_redir(t_token **tok)
{
	t_ast	*ast;
	t_ast	*reder;

	ast = parse_cmd(tok);
	if ((*tok)->type == RIN || (*tok)->type == ROUT || (*tok)->type == HEREDOC
		|| (*tok)->type == APPEND)
	{
		reder = redire_info(tok);
		if (!reder)
			return (NULL);
		while ((*tok)->type != AND && (*tok)->type != OR && (*tok)->type != PIPE
			&& (*tok)->type != END)
		{
			if ((*tok)->type != WORD && !addback_redir(reder, redire_info(tok)))
				return (NULL);
			(!ast && (*tok)->type == WORD) && (ast = parse_cmd(tok));
			if (ast && (*tok)->type == WORD)
				addb_list(ast, tok);
		}
		return (addback_redir(reder, ast), reder);
	}
	return (ast);
}

// pour gerer les commandes entre "()"
t_ast	*parse_sub(t_token **tok)
{
	t_ast	*ast;

	*tok = (*tok)->next;
	if ((*tok)->type == CPAR)
		return (NULL);
	while ((*tok)->type != CPAR)
	{
		ast = new_sub(parse_oper(tok));
		if (!((t_subsh *)ast)->sub)
			return (NULL);
	}
	*tok = (*tok)->next;
	return (ast);
}

// fonction pour analyser une séquence de commandes et des pipes
t_ast	*parse_pipe(t_token **tok)
{
	t_ast	*ast;

	ast = parse_redir(tok);
	if (!ast)
		return (NULL);
	while ((*tok)->type == PIPE)
	{
		*tok = (*tok)->next;
		ast = new_oper(PIPE, ast, parse_redir(tok));
		if (!((t_operator *)ast)->right)
			return (NULL);
	}
	return (ast);
}

// fonction analyse une séquence de commandes et d'opérateurs logiques
t_ast	*parse_oper(t_token **tok)
{
	t_ast	*ast;

	ast = parse_pipe(tok);
	if (!ast)
		return (NULL);
	while (((*tok)->type == AND || (*tok)->type == OR))
	{
		ast = new_oper((*tok)->type, ast, NULL);
		*tok = (*tok)->next;
		((t_operator *)ast)->right = parse_pipe(tok);
		if (!((t_operator *)ast)->right)
			return (NULL);
	}
	return (ast);
}
