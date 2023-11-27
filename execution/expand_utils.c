/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:29:45 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:29:46 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* fonction est utilisée pour gérer les cas 
    où un caractère ('$') est suivi 
     d'un caractère qui n'est pas valide 
      pour une variable d'environnement*/
char	*handle_non_valid_variable(char *str, int *i)
{
	int		j;
	char	*var;

	j = *i + 1;
	while (str[j] && str[j] != '$')
		j++;
	var = ft_substr(str, *i, j - *i);
	*i = j;
	return (ft_strdup(var));
}

/*fonction recherche dans la chaîne str à partir de l'index i
la partie qui n'est pas une variable d'environnement 
(c'est-à-dire, ne commence pas par '$')*/
char	*handle_non_variable(char *str, int *i)
{
	int	j;

	j = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, j, *i - j));
}

/*fonction recherche et remplace les variables d'environnement 
dans une chaîne de caractères par leurs valeurs correspondantes 
à partir d'une liste d'environnement*/
char	*handle_variable(char *str, t_env *env, int *i)
{
	char	*p;
	int		j;

	j = *i + 1;
	if (str[j] && (str[j] == '_' || ft_isalpha(str[j])))
		p = handle_env_variable(str, env, i, j);
	else if (str[j] == '?')
	{
		*i += 2;
		p = ft_itoa(g_stat % 255);
	}
	else
		p = handle_non_valid_variable(str, i);
	return (p);
}

/*fonction cherche une variable d'environnement (par exemple, $HOME)
  dans la chaîne str à partir de la position indiquée par *i
   et retourne la valeur de la variable d'environnement
    trouvée dans la liste env*/
char	*handle_env_variable(char *str, t_env *env, int *i, int j)
{
	char	*var;

	while (str[j] && (str[j] == '_' || ft_isalnum(str[j])))
		j++;
	var = ft_substr(str, *i + 1, j - *i - 1);
	*i = j;
	return (ft_strdup(getv(var, env)));
}
