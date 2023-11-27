/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:34:42 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:34:44 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*prend une liste chaînée de variables d'environnement 
   de type t_env et la transforme en un tableau 
    de chaînes de caractères (format "variable=valeur") */
char	**trans_myenv(t_env *myenv)
{
	int		i;
	int		len;
	char	**env;

	i = 0;
	len = ft_lstsize(myenv);
	env = gc(sizeof(char *) * (len + 1), 1, 0);
	env[len] = 0;
	while (myenv)
	{
		(myenv->print) && (env[i++] = ft_strjoin_sp(myenv->variable,
					myenv->value, '='));
		myenv = myenv->next;
	}
	return (env);
}

/* prépare les arguments de la commande en se basant 
     sur la liste de tokens en effectuant 
	   les manipulations nécessaires
   renvoie un tableau de chaînes de caractères 
     prêt à être passé à l'exécution de la commande.*/
char	**trans_list(t_token *list, t_env *myenv)
{
	t_vartrans_list	v;

	expand_change(&list, myenv);
	wildcard_change(&list);
	v.arg = gc(sizeof(char *) * (size_token(list) + 1), 1, 0);
	v.i = 0;
	v.str = NULL;
	while (list)
	{
		(!list->down) && (v.arg[v.i++] = list->token);
		if (list->down)
		{
			v.tmp = list;
			while (v.tmp)
			{
				v.str = ft_strjoin(v.str, expand_prime(v.tmp->token, myenv));
				v.tmp = v.tmp->down;
			}
			v.arg[v.i++] = v.str;
			v.str = NULL;
		}
		list = list->next;
	}
	return (v.arg[v.i] = 0, v.arg);
}

/*déterminer le chemin valide d'un exécutable en se basant 
sur une commande donnée (arg) en utilisant les variables d'environnement
 stockées dans la structure t_env*/
char	*valid_path(char *arg, t_env *myenv)
{
	int		i;
	char	*new_arg;
	char	**paths;
	t_env	*tmp;

	i = -1;
	if (*arg == '/' || !access(arg, X_OK) || !*arg)
		return (arg);
	tmp = ft_lstchr(myenv, "PATH");
	if (!tmp)
		return (fd_printf(2, "%s: No such file or directory\n", arg), NULL);
	paths = ft_split(tmp->value, ':');
	while (paths[++i])
	{
		new_arg = ft_strjoin_sp(paths[i], arg, '/');
		if (!access(new_arg, X_OK))
			return (new_arg);
	}
	return (paths[0]);
}

/*exécute des commandes en les lançant dans de nouvelles fenêtres virtuelles
en gérant les entrées/sorties
et en récupérant des informations sur leur exécution 
Elle gère également des commandes spéciales si nécessaire*/
void	exec_cmd(t_ast *ast, t_env **myenv)
{
	char	**arg;
	pid_t	pid;
	int		stat;
	char	*vpath;

	arg = trans_list(((t_command *)ast)->list, *myenv);
	if (builting(myenv, arg) || !*arg[0])
		return ;
	vpath = valid_path(arg[0], *myenv);
	if (!vpath)
		return ;
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (!pid)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execve(vpath, arg, trans_myenv(*myenv));
		fd_printf(2, "Exec : command not found: %s\n", arg[0]);
		exit(127);
	}
	waitpid(pid, &stat, WUNTRACED);
	exit_status(stat);
}
