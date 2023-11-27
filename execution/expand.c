/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:19:59 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:20:32 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*renvoie la valeur associée à la variable 
    d'environnement str dans la structure env
Si la variable n'est pas trouvée elle renvoie NULL*/
char	*getv(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_memcmp(env->variable, str, ft_strlen(env->variable) + 1)
			&& env->print != -2)
			return (str = env->value, str);
		env = env->next;
	}
	return (NULL);
}

/*parcourt la chaîne de caractères str
    recherche les variables d'environnement 
(qui sont des portions de texte commencant par "$") 
et les remplace par leur valeur à partir de la liste env
retourne la nouvelle chaîne de caractères 
  avec les substitutions de variables effectuées*/
char	*expand_prime(char *str, t_env *env)
{
	int		i;
	char	*s;
	char	*p;

	i = 0;
	s = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '$')
			p = handle_non_variable(str, &i);
		else
			p = handle_variable(str, env, &i);
		s = _strjoin(s, p);
	}
	return (s);
}

/* fonction  transforme une chaîne de 
     caractères en une liste de morceaux (tokens) 
en remplaçant les variables d'environnement par leurs valeurs*/
t_token	*expand(char *str, t_env *env, int flag)
{
	int		i;
	t_token	*head;
	char	**strs;

	i = -1;
	head = NULL;
	if (!flag)
		return (addtok(&head, ft_newtoken(WORD, expand_prime(str, env), 0, 0)),
			head);
	strs = split_wc(expand_prime(str, env));
	if (!*strs)
		return (addtok(&head, ft_newtoken(WORD, ft_strdup(""), 0, 0)), head);
	while (strs[++i])
		addtok(&head, ft_newtoken(WORD, strs[i], 0, 0));
	return (head);
}
