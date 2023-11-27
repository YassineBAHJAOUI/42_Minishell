/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:28:33 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 17:32:44 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_id(char *ident)
{
	if (!ft_isalpha(*ident) && *ident != '_')
		return (0);
	ident++;
	while ((ft_isalnum(*ident) || *ident == '_') && *ident)
		ident++;
	if (!*ident)
		return (1);
	return (0);
}

//ligne 37 Si l'identificateur est valide,
//supprimer la variable d'environnement correspondante
void	unset(t_env **myenv, char **arg)
{
	int	i;

	i = 0;
	set_statu(0);
	while (arg[++i])
	{
		if (check_id(arg[i]))
			delete_node(myenv, arg[i]);
		else
		{
			fd_printf(2, "unset: `%s': not a valid identifier\n", arg[i]);
			set_statu(1);
		}
	}
}
