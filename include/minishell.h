/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:35:24 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:35:25 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libgc/gc.h"
# include "../Libft-42/libft.h"
# include <dirent.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <paths.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lexer.h"
# include "parser.h"
# include "execution.h"
# include "builtins.h"

extern int			g_stat;

typedef struct s_varibles
{
	char	*cmdl;
	t_ast	*ast;
	t_env	*myenv;
	t_token	*tok;
}			t_varibles;

#endif
