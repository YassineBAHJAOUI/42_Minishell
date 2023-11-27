/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exitstatus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:20:52 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:21:10 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*réagit lorsque vous appuyez sur Ctrl+C 
pour arrêter un programme. Elle effectue ces actions :
Ignore Ctrl+C.
Passe à la ligne suivante.
Efface la commande en cours.
Indique que quelque chose s'est mal 
passé en définissant un statut d'erreur*/
void	param_sig(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_statu(1);
}

void	exit_status(int status)
{
	if (WIFEXITED(status))
		g_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_stat = WTERMSIG(status);
}

void	set_statu(int status)
{
	g_stat = status;
}
