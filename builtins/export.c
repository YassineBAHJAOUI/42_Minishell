/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:32:58 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 17:55:30 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_id(char *ident, char *arg)
{
	if (!ft_isalpha(*ident) && *ident != '_')
		return (0);
	ident++;
	while ((ft_isalnum(*ident) || *ident == '_') && *ident)
		ident++;
	if (*ident == '+' && !*(ident + 1) && ft_strchr(arg, '='))
		return (-1);
	if (!*ident)
		return (1);
	return (0);
}

// ligne 43 Supprime le caractère '+' en début de variable
// ligne 45 Recherche de la variable dans la liste chaînée
/* ligne 46 Si la variable n'était pas préalablement définie 
            et qu'elle existe déjà ne rien faire*/
// ligne 48 Si la variable n'existe pas la créer et l'ajouter à la liste chaînée
// ligne 50 Si la variable existe, mettre à jour sa valeur
// ligne 53 Si le flag n'est pas activé mettre simplement à jour la valeur
// ligne 55 Sinon concatener la nouvelle valeur avec ancien
void	addvalue(t_env **myenv, char **sub, int prenv, int flag)
{
	char	*tri;
	char	*oldval;
	t_env	*find;

	tri = trim_allo(sub[0], "+");
	free(sub[0]);
	find = ft_lstchr(*myenv, tri);
	if (!prenv && find)
		return (free(tri), free(sub[1]));
	if (!find)
		return (addbenv(myenv, newenv(tri, sub[1], prenv)));
	find->print = 1;
	oldval = find->value;
	free(tri);
	if (!flag)
		return (find->value = sub[1], free(oldval));
	return (find->value = join_allo(oldval, sub[1]), free(sub[1]));
}

void	error_export(char **sub, char *arg)
{
	fd_printf(2, "export: `%s': not a valid identifier\n", arg);
	set_statu(1);
	free(sub[0]);
	free(sub[1]);
	free(sub);
}

// ligne 83 Si la commande export est appelée sans arguments
//          afficher les variables d'environnement
// ligne 88 Utiliser la fonction subbing 
//          pour extraire le nom de la variable et sa valeur
// ligne 89 Vérifier si le nom de la variable est valide
// ligne 91 Afficher une erreur si le nom de la variable n'est pas valide
// ligne 94 Condition 1: Ajouter une valeur à une variable existante
// ligne 96 Condition 2: Mettre à jour le contenu d'une variable existante
// ligne 98 Condition 3: Ajouter ou mettre à jour 
//          une variable avec une nouvelle valeur spécifiée
void	export(t_env **myenv, char **arg)
{
	int		i;
	char	**sub;

	set_statu(0);
	if (!arg[1])
		return (print_export(*myenv));
	i = 0;
	while (arg[++i])
	{
		sub = subbing(arg[i]);
		if (!check_id(sub[0], arg[i]))
		{
			error_export(sub, arg[i]);
			continue ;
		}
		else if (check_id(sub[0], arg[i]) == -1)
			addvalue(myenv, sub, 1, 1);
		else if (check_id(sub[0], arg[i]) && !ft_strchr(arg[i], '='))
			addvalue(myenv, sub, 0, 0);
		else if (check_id(sub[0], arg[i]) && ft_strchr(arg[i], '='))
			addvalue(myenv, sub, 1, 0);
		free(sub);
	}
}
