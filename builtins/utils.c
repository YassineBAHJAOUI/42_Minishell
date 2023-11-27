/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:00:05 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:00:06 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_digit(char *str)
{
	int	i;

	i = -1;
	if ((str[0] == '-' || str[0] == '+') && !str[1])
		return (0);
	(str[0] == '-' || str[0] == '+') && (i += 1);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	swap_data(t_env *a, t_env *b)
{
	int		tm;
	char	*c;

	c = a->variable;
	a->variable = b->variable;
	b->variable = c;
	c = a->value;
	a->value = b->value;
	b->value = c;
	tm = a->print;
	a->print = b->print;
	b->print = tm;
}

void	print_export(t_env *myenv)
{
	t_utils	v;

	v.exp = NULL;
	while (myenv)
	{
		addbenv(&v.exp, newenv(myenv->variable, myenv->value, myenv->print));
		myenv = myenv->next;
	}
	v.tmp2 = v.exp;
	while (v.exp)
	{
		v.tmp = v.exp;
		while (v.tmp)
		{
			if (ft_strcmp(v.exp->variable, v.tmp->variable) >= 0)
				swap_data(v.exp, v.tmp);
			v.tmp = v.tmp->next;
		}
		(v.exp->print > 0) && (printf("declare -x %s=\"%s\"\n", v.exp->variable,
					v.exp->value));
		(v.exp->print == 0) && (printf("declare -x %s\n", v.exp->variable));
		v.exp = v.exp->next;
	}
	ft_lstclear(&v.tmp2);
}
