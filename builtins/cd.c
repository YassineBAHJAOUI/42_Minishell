/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:43:31 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 17:59:55 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ligne 26 Recherche de la variable dans la liste d'environnement
// ligne 27 La variable n'existe pas et le flag est activé 
//          donc on crée une nouvelle entrée
// ligne 31 La variable n'existait pas, renvoie NULL
// ligne 33 La variable existe met à jour sa valeur
//          avec la nouvelle valeur (pwd)
// ligne 38 Renvoie l'ancienne valeur de la variable (avant mise à jour)
char	*cd_env(t_env *myenv, const char *variable, char *pwd, int flag)
{
	t_env	*find;

	find = ft_lstchr(myenv, variable);
	if (!find)
	{
		if (flag)
			addbenv(&myenv, newenv(dup_alloc(variable), pwd, 1));
		return (NULL);
	}
	if (flag)
	{
		free(find->value);
		find->value = pwd;
	}
	return (find->value);
}

// ligne 52 Vérifier si le chemin (path) est défini
// ligne 54 Obtenir le répertoire de travail actuel (cwd)
// ligne 55 Vérifier si la récupération du cwd a échoué
// ligne 60 Changer de répertoire
// ligne 61 Vérifier si le changement de répertoire a échoué
// ligne 63 64 Mettre à jour les variables d'environnement "OLDPWD" et "PWD"
void	execd(t_env *myenv, const char *path, const char *var)
{
	int		ret;
	char	*pwd;

	if (!path)
		return (set_statu(1), fd_printf(2, "cd %s not set\n", var));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_statu(1), chdir(path), fd_printf(2,
				"cd: error retrieving current directory: getcwd: \
cannot access \
parent directories: No such file or directory\n"));
	ret = chdir(path);
	if (ret != 0)
		return (set_statu(1), perror(path));
	cd_env(myenv, "OLDPWD", pwd, 1);
	cd_env(myenv, "PWD", getcwd(NULL, 0), 1);
}

void	cd(t_env *myenv, char **arg)
{
	char	*oldpwd;

	set_statu(0);
	if (!ft_memcmp("~", arg[1], 2) || !arg[1])
		return (execd(myenv, cd_env(myenv, "HOME", NULL, 0), "HOME"));
	if (!ft_memcmp("-", arg[1], 2))
	{
		oldpwd = ft_strdup(cd_env(myenv, "OLDPWD", NULL, 0));
		execd(myenv, oldpwd, "OLDPWD");
		if (oldpwd)
			return (printf("%s\n", oldpwd), free(NULL));
		return ;
	}
	return (execd(myenv, arg[1], ""));
}
