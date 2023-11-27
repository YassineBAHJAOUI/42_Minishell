/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_oper_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:33:35 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:33:36 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*cette fonction crée un nouveau processus (sous-shell) 
    et exécute la commande spécifiée dans ast à l'intérieur de ce sous-shell
  Elle utilise l'environnement myenv pour obtenir des 
    variables d'environnement si nécessaire
  Une fois que la commande dans le sous-shell est terminée
    la fonction renvoie le statut de sortie du sous-shell*/
void	exec_subshell(t_ast *ast, t_env *myenv)
{
	int	pid;
	int	stat;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (!pid)
	{
		execution(((t_subsh *)ast)->sub, &myenv);
		exit(g_stat);
	}
	waitpid(pid, &stat, WUNTRACED);
	exit_status(stat);
}

/*gère la logique d'exécution des opérations logiques "et" et "ou" 
en fonction du statut de sortie des commandes de gauche et de droite*/
void	exec_oper(t_ast *ast, t_env *myenv)
{
	execution(((t_operator *)ast)->left, &myenv);
	if (ast->type == AND && !g_stat)
		execution(((t_operator *)ast)->right, &myenv);
	if (ast->type == OR && g_stat)
		execution(((t_operator *)ast)->right, &myenv);
}
