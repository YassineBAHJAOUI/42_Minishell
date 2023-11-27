/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:36:38 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:39:51 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

// initialiser une structure `t_norm` avec des valeurs par défaut.
void	norminit(t_norm *ptr)
{
	ptr->i = -1;
	ptr->token = 0;
	ptr->down = 0;
	ptr->dq = false;
	ptr->sq = false;
	ptr->space = true;
	ptr->op = 0;
	ptr->cp = 0;
}

/* Fonction pour traiter certains caractères spéciaux
    notamment les guillemets simples les guillemets doubles
	  les opérateurs de redirection, les parenthèses, et les espaces.*/
void	norm_1(t_norm *n, char *c)
{
	(c[n->i] == '\'') && (n->sq = !n->sq);
	(c[n->i] == '\"') && (n->dq = !n->dq);
	(ft_strchr("|<>&", c[n->i]) && c[n->i] == c[n->i + 1]) && (n->x = 1);
	(c[n->i] != '\'' && c[n->i] != '\"') && (n->space = true);
	(c[n->i] == '(') && (n->op += 1);
	(c[n->i] == ')') && (n->cp += 1);
	if (!allspace(n->i, c) && c[n->i] != '\'' && c[n->i] != '\"'
		&& c[n->i] != ' ' && c[n->i] != '\t')
		addtok(&n->token, ft_newtoken(getflag(c[n->i], n->x), ft_substr(c, n->i,
					n->x + 1), 0, 0));
	if (c[n->i] == ' ' || c[n->i] == '\t')
	{
		while ((c[n->i] == ' ' || c[n->i] == '\t') && c[n->i])
			n->i++;
		n->i--;
	}
	n->i += n->x;
}

// traiter les cas où des guillemets simples ou doubles sont ouverts.
// crée des jetons pour les chaînes entre guillemets.
void	norm_2(t_norm *n, char *c)
{
	if (n->space)
	{
		addtok(&n->token, ft_newtoken(WORD, getq(c, &n->i, c[n->i - 1]),
				(n->dq == true), 0));
		n->space = false;
	}
	else if (!n->space)
	{
		n->down = lasttok(n->token);
		while (n->down->down)
			n->down = n->down->down;
		n->down->down = ft_newtoken(WORD, getq(c, &n->i, c[n->i - 1]),
				(n->dq == true), 0);
	}
}

// traiter les mots non entourés de guillemets.
// crée des jetons pour ces mots.
void	norm_3(t_norm *n, char *c)
{
	if (n->space)
	{
		addtok(&n->token, ft_newtoken(WORD, getword(c, &n->i), 1, 1));
		n->space = false;
	}
	else if (!n->space)
	{
		n->down = lasttok(n->token);
		while (n->down->down)
			n->down = n->down->down;
		n->down->down = ft_newtoken(WORD, getword(c, &n->i), 1, 1);
	}
}

/* Fonction principale pour analyser la chaîne de caractères `c` 
   produire une liste de jetons. */
t_token	*tokenizer(char *c)
{
	t_norm	n;

	norminit(&n);
	while (c[++(n.i)])
	{
		n.x = 0;
		if ((n.sq && c[n.i] != '\'') || (n.dq && c[n.i] != '\"'))
			norm_2(&n, c);
		else if (ft_strchr("\"\'|<>&() \t", c[n.i]))
			norm_1(&n, c);
		else if (!ft_strchr("\"\'|<>&() \t", c[n.i]) && (!n.dq || !n.sq))
			norm_3(&n, c);
	}
	if ((n.sq || n.dq) || (n.op != n.cp))
		return (fd_printf(2, "Syntax : Quote Unfound\n"), NULL);
	if (n.op != n.cp)
		return (fd_printf(2, "Syntax : Need a parantes\n"), NULL);
	addtok(&n.token, ft_newtoken(END, ft_strdup("newline"), 0, 0));
	return (n.token);
}
