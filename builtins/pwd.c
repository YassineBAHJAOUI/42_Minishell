/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:28:16 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 17:28:18 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	pwd[PATH_MAX];

	set_statu(0);
	getcwd(pwd, PATH_MAX);
	ft_putendl_fd(pwd, STDOUT_FILENO);
}
