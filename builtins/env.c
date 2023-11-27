/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:00:14 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:00:41 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_env *myenv)
{
	set_statu(0);
	while (myenv)
	{
		if (myenv && myenv->print > 0)
			printf("%s=%s\n", myenv->variable, myenv->value);
		myenv = myenv->next;
	}
}
