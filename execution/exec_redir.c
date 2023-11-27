/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:32:58 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:33:00 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*gère la redirection heredoc en lisant le texte entré par l'utilisateur*/
int	expand_herdoc(int fd_in, t_env *myenv)
{
	int		fd[2];
	char	*gnl;

	if (pipe(fd) == -1)
		return (perror("pipe"), exit(1), 0);
	gnl = expand_prime(get_next_line(fd_in), myenv);
	while (gnl)
	{
		write(fd[1], gnl, ft_strlen(gnl));
		gnl = expand_prime(get_next_line(fd_in), myenv);
	}
	(gnl) && (write(fd[1], gnl, ft_strlen(gnl)));
	return (close(fd[1]), fd[0]);
}

/*gérer la redirection de fichiers dans un shell
   assure que les fichiers sont correctement redirigés
     que ce soit en lecture ou en écriture
  en fonction des informations contenues dans la structure redir
    prend en compte les variables d'environnement (myenv) pour résoudre 
      les chemins des fichiers si nécessaire
  En fin permet de contrôler les entrées et les sorties de 
    données vers et depuis des fichiers*/
int	create_duping(t_redir *redir, t_env *myenv)
{
	int		fd;
	int		std;
	char	**file;

	(redir->typeredir == RIN || redir->typeredir == HEREDOC) && (std = 0);
	(redir->typeredir == ROUT || redir->typeredir == APPEND) && (std = 1);
	if (redir->typeredir != HEREDOC)
	{
		file = trans_list(redir->tok, myenv);
		if (file[1])
			return (fd_printf(2, "%s: ambiguous redirect\n", redir->tok->token),
				exit(1), 0);
		fd = open(file[0], redir->flags, 0664);
		if (fd == -1)
			return (perror(expand_prime(redir->tok->token, myenv)), exit(1), 0);
		if (dup2(fd, std) == -1)
			return (perror("dup2 "), exit(1), 0);
		return (close(fd), 1);
	}
	(redir->tok->hdoc && !redir->tok->down)
		&& (redir->fd_in = expand_herdoc(redir->fd_in, myenv));
	if (dup2(redir->fd_in, std) == -1)
		return (perror("dup2"), exit(1), 0);
	return (1);
}

/*exécution de commandes avec des redirections en mettant en place 
les redirections nécessaires et en exécutant la commande*/
void	exec_redir(t_ast *ast, t_env *myenv)
{
	int	pid;
	int	statu;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (!pid)
	{
		while (ast && ast->type == REDIR && create_duping((t_redir *)ast,
				myenv))
			ast = ((t_redir *)ast)->trdr;
		execution(ast, &myenv);
		exit(0);
	}
	waitpid(pid, &statu, 0);
	exit_status(statu);
}
