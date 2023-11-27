/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:35:17 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:35:18 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define RIGHT 0
# define LEFT 1

t_token		*wildmatch(char *pattern);
void		execution(t_ast *ast, t_env **myenv);
void		exec_pipe(t_ast *ast, t_env *myenv);
void		exec_cmd(t_ast *ast, t_env **myenv);
void		exec_redir(t_ast *ast, t_env *myenv);
void		exec_subshell(t_ast *ast, t_env *myenv);
void		exec_oper(t_ast *ast, t_env *myenv);
char		*expand_prime(char *str, t_env *env);
t_token		*expand(char *str, t_env *env, int flag);
void		expand_change(t_token **list, t_env *myenv);
void		wildcard_change(t_token **list);
void		close_pipe(int fds[2]);
int			count_words(char *str, char c);
void		exit_status(int status);
void		set_statu(int status);
void		param_sig(int signum);
char		**trans_list(t_token *list, t_env *myenv);
char		*handle_non_valid_variable(char *str, int *i);
char		*handle_env_variable(char *str, t_env *env, int *i, int j);
char		*handle_variable(char *str, t_env *env, int *i);
char		*handle_non_variable(char *str, int *i);
char		*getv(char *str, t_env *env);
typedef struct s_vartrans_list
{
	int		i;
	char	*str;
	char	**arg;
	t_token	*tmp;
}			t_vartrans_list;
#endif