/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:44:12 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:44:14 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction pour ajouter une redirection à un redirection existant.
int	addback_redir(t_ast *tree, t_ast *addin)
{
	if (!addin || !tree)
		return (0);
	while (((t_redir *)tree)->trdr)
		tree = ((t_redir *)tree)->trdr;
	((t_redir *)tree)->trdr = addin;
	return (1);
}

/* Fonction pour ajouter un nouveau jeton 
    à une liste de jetons associée à un commande*/
void	addb_list(t_ast *ast, t_token **tok)
{
	t_token	*find;

	find = lasttok(((t_command *)ast)->list);
	find->next = ft_newtoken(0, NULL, 0, 0);
	find = find->next;
	find->type = (*tok)->type;
	find->hdoc = (*tok)->hdoc;
	find->expand = (*tok)->expand;
	find->token = (*tok)->token;
	find->down = (*tok)->down;
	find->prev = (*tok)->prev;
	find->next = NULL;
	*tok = (*tok)->next;
}

// fonction pour cree un nouveau token 
t_token	*newtoken(t_token *node)
{
	t_token	*token;

	token = gc(sizeof(t_token), 1, 0);
	token->token = node->token;
	token->type = node->type;
	token->down = node->down;
	token->expand = node->expand;
	token->hdoc = node->hdoc;
	token->expand = node->expand;
	token->hdoc = node->hdoc;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

/* Fonction  collecter des informations sur la redirection
    puis crée la redirection*/
t_ast	*redire_info(t_token **tok)
{
	int		type;
	t_ast	*redir;
	t_token	*hold;

	if ((*tok)->type != RIN && (*tok)->type != ROUT && (*tok)->type != HEREDOC
		&& (*tok)->type != APPEND)
		return (NULL);
	type = (*tok)->type;
	redir = new_reder();
	((t_redir *)redir)->typeredir = type;
	((t_redir *)redir)->flags = O_RDONLY;
	if (type == ROUT || type == APPEND)
		((t_redir *)redir)->flags = O_CREAT | O_WRONLY | ((type == ROUT)
				* O_TRUNC + !(type == RIN) * O_APPEND);
	*tok = (*tok)->next;
	if ((*tok)->type != WORD)
		return (NULL);
	hold = newtoken(*tok);
	((t_redir *)redir)->tok = hold;
	((t_redir *)redir)->arg = join_tokens(hold);
	(type == HEREDOC)
		&& (((t_redir *)redir)->fd_in = heredoc(join_tokens(*tok)));
	if (type == HEREDOC && !((t_redir *)redir)->fd_in)
		return ((*tok)->type = SIGHER, NULL);
	return (*tok = (*tok)->next, redir);
}
