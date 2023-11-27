/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:18:37 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:18:39 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_ast *ast, t_env **myenv)
{
	signal(SIGINT, SIG_IGN);
	if (!ast)
		return ;
	if (ast->type == PIPE)
		exec_pipe(ast, *myenv);
	else if (ast->type == AND || ast->type == OR)
		exec_oper(ast, *myenv);
	else if (ast->type == REDIR)
		exec_redir(ast, *myenv);
	else if (ast->type == WORD)
		exec_cmd(ast, myenv);
	else if (ast->type == SUBSHELL)
		exec_subshell(ast, *myenv);
	else
		return ;
}
