/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:18:51 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:19:41 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*s'assure que les parties finales de obj 
correspondent aux parties finales de pattern
tout en tenant compte des caractères génériques '*'
si la correspondance est réussie la fonction renvoie true
sinon elle renvoie false*/
bool	match_3(char *obj, char *pattern)
{
	char	**tok;
	int		i;
	char	*res;

	tok = ft_split(pattern, '*');
	i = 0;
	while (tok[i])
	{
		res = ft_strstr(obj, tok[i]);
		if (res)
		{
			obj += ft_strlen(tok[i]);
			i++;
		}
		else
			return (false);
	}
	return (true);
}

/*permet de vérifier si la fin de pattern correspond à la fin de obj
tout en tenant compte du caractère * comme un joker pouvant représenter
plusieurs caractères si la correspondance est réussie 
la fonction renvoie true sinon elle renvoie false*/
bool	match_2(char *obj, char *pattern)
{
	int	j;
	int	i;

	j = ft_strlen(obj) - 1;
	i = ft_strlen(pattern);
	while (--i >= 0 && pattern[i] != '*')
	{
		if (pattern[i] != obj[j])
			return (false);
		j--;
	}
	return (match_3(ft_substr(obj, 0, j + 1), ft_substr(pattern, 0, i + 1)));
}

/*vérifier si une chaîne de caractères obj 
    correspond à un motif (pattern) donné
Elle renvoie true si la correspondance 
    est réussie et false sinon.*/
bool	match(char *obj, char *pattern)
{
	int		i;
	char	*tok;
	int		len;

	i = 0;
	tok = NULL;
	if (pattern[0] == '*' && obj[0] == '.')
		return (false);
	if (*pattern != '*')
	{
		while (pattern[i] && pattern[i] != '*')
			i++;
		tok = ft_substr(pattern, 0, i);
		if (ft_memcmp(obj, tok, ft_strlen(tok)))
			return (false);
	}
	len = 0;
	(tok) && (len = ft_strlen(tok));
	return (match_2(obj + len, pattern + len));
}

/*fonction permet de trouver tous les fichiers 
   dans le répertoire courant qui correspondent
     à un motif spécifié et elle crée une liste 
       de tokens pour ces fichiers.*/
t_token	*wildmatch(char *pattern)
{
	DIR				*dir;
	struct dirent	*obj;
	t_token			*lst;

	lst = NULL;
	dir = opendir(".");
	obj = readdir(dir);
	while (obj)
	{
		if (match(obj->d_name, pattern))
			addtok(&lst, ft_newtoken(0, ft_strdup(obj->d_name), 0, 0));
		obj = readdir(dir);
	}
	closedir(dir);
	if (!lst)
		addtok(&lst, ft_newtoken(0, pattern, 0, 0));
	return (lst);
}
