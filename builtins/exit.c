/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:01:00 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:16:39 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *myenv)
{
	t_env	*current;
	t_env	*next;

	current = myenv;
	while (current != NULL)
	{
		next = current->next;
		free(current->variable);
		free(current->value);
		free(current);
		current = next;
	}
}

/* ligne 49 Si aucun argument n'est fourni (seulement la commande "exit")
	afficher un message et quitter avec le code de statut global (g_stat)*/
/* ligne 51 Si l'argument n'est pas un nombre
            afficher un message d'erreur et quitter*/
// ligne 54 Si l'argument est un nombre et aucun autre argument n'est fourni.
/* ligne 56 Convertir l'argument en nombre, en tenant compte 
            d'un éventuel signe négatif.*/
/* ligne 57 Si une erreur s'est produite lors de la conversion 
            afficher un message d'erreur et quitter */
// ligne 61 sinon afficher "exit" et quitter
/* ligne 63 Si des arguments supplémentaires sont fournis afficher un message 
            d'erreur et définir le code de statut global sur 1.*/
void	ft_exit(char **arg, t_env **myenv)
{
	int				flag;
	long long int	a;

	flag = 0;
	if (!arg[1])
		return (write(2, "exit\n", 5), free_env(*myenv), exit(g_stat));
	else if (!is_digit(arg[1]))
		return (fd_printf(2, "exit\nexit: %s: numeric argument required\n",
				arg[1]), free_env(*myenv), exit(255));
	else if (is_digit(arg[1]) && !arg[2])
	{
		a = atoi_exit(arg[1], &flag);
		if (flag < 0)
			return (a = 255,
				fd_printf(2, "exit\nexit: %s: numeric argument required\n",
					arg[1]), free_env(*myenv), exit(a % 256));
		return (fd_printf(2, "exit\n"), free_env(*myenv), exit(a % 256));
	}
	else
		return (fd_printf(2, "exit\nexit: too many \
		arguments\n"), set_statu(1), free_env(*myenv));
}
