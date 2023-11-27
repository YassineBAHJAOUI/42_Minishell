/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:40:48 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:40:51 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* fonction parser commence par vérifier 
    si la liste de jetons est vide
      ou si le dernier jeton est de type END
   Si l'une de ces conditions est vraie
     l'analyse s'arrête et résultant est renvoyé*/
t_ast	*parser(t_token **tok)
{
	t_ast	*tree;

	if (!*tok || (*tok)->type == END)
		return (NULL);
	tree = parse_oper(tok);
	if ((!tree || (*tok)->type != END) && (*tok)->type != SIGHER)
	{
		set_statu(258);
		fd_printf(2, "Syntax : Error unexpected token `%s'\n", (*tok)->token);
		return (NULL);
	}
	return (tree);
}
