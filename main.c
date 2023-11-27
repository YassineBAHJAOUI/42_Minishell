/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:03:56 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 17:05:48 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stat = 0;

int	main(int ac, char **av, char **env)
{
	t_varibles	v;

	(void)av;
	(void)ac;
	signal(SIGQUIT, SIG_IGN);
	dupenv(&v.myenv, env);
	gc(0, 0, 1);
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, param_sig);
		v.cmdl = readline("minishell-$ ");
		if (v.cmdl == NULL)
		{
			free_env(v.myenv);
			break ;
		}
		v.tok = tokenizer(v.cmdl);
		v.ast = parser(&v.tok);
		execution(v.ast, &v.myenv);
		if (*v.cmdl)
			add_history(v.cmdl);
		free(v.cmdl);
		gc(0, 0, 0);
	}
}
