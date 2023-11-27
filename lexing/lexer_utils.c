/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:36:34 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:38:42 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

// extraire un mot suite de caractères sans espaces ni caractères spéciaux
// Elle renvoie le mot trouvé et met à jour l'indice `*index`.
char	*getword(char *str, int *index)
{
	int	i;
	int	j;

	i = *index;
	j = i;
	while (str[i] && !ft_strchr("\"\'|<>&() \t", str[i]))
		i++;
	return (*index = i - 1, ft_substr(str, j, i - j));
}

// extraire une chaîne entre guillemets (simple ou double) de la chaîne `str`
char	*getq(char *str, int *index, char c)
{
	int	i;
	int	j;

	i = *index;
	j = i;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (*index = i - 1, ft_substr(str, j, i - j));
	return (*index = i - 1, ft_substr(str, j, i - j));
}

/* obtenir le type de jeton (`t_flag`) en fonction 
     du caractère `c` et de la valeur de `flag`. 
   classer les caractères en différents types de jetons*/
int	getflag(char c, int flag)
{
	char	*str;
	int		i;

	i = -1;
	str = "\"\'|<>()";
	while (str[++i])
		if (str[i] == c)
			break ;
	if (c == '&' && !flag)
		return (0);
	else if (c == '&' && flag)
		return (9);
	(flag) && (i += 7);
	return (i + 1);
}

// vérifier si tous les caractères à partir de l'indice `i` sont des espaces.
int	allspace(int i, char *c)
{
	while (c[i] && c[i] == ' ')
		i++;
	if (c[i])
		return (0);
	else
		return (1);
}
