/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:17:44 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 17:27:45 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_option(char *arg)
{
	int	i;

	i = 0;
	if ((arg[i] != '-') || (arg[i] == '-' && arg[1] != 'n'))
		return (0);
	while (arg[++i])
	{
		if (arg[0] != '-' || arg[i] != 'n')
			return (0);
	}
	return (1);
}

//ligne 45 Si l'option -n est présente, concaténer les arguments avec un espace
//ligne 47 Sinon, concaténer les arguments avec un espace
//ligne 52 Si l'option -n est présente, afficher sans sauter une ligne
void	echo(char **arg)
{
	int		i;
	char	*str;

	set_statu(0);
	if (!arg[1])
		return (ft_putendl_fd("", 1));
	str = NULL;
	i = 0;
	while (arg[++i])
	{
		if (valid_option(arg[1]) && !valid_option(arg[i]))
			str = ft_strjoin_sp(str, arg[i], ' ');
		else if (!valid_option(arg[1]))
			str = ft_strjoin_sp(str, arg[i], ' ');
	}
	if (!str)
		return ;
	if (valid_option(arg[1]))
		return (ft_putstr_fd(str, 1));
	return (ft_putendl_fd(str, 1));
}
