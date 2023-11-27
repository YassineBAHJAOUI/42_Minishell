/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:49:14 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 16:49:16 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_new(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static char	*stock_str(char *stock)
{
	char	*new_s;

	if (ft_strchr(stock, '\n'))
	{
		new_s = ft_strdup(ft_strchr(stock, '\n') + 1);
		return (new_s);
	}
	new_s = NULL;
	return (new_s);
}

static char	*stop_at_nel(char *stock)
{
	char	*gnl;

	if (!stock)
		return (NULL);
	if (stock[0] == '\0')
		return (NULL);
	if (ft_strchr(stock, '\n'))
	{
		gnl = ft_substr(stock, 0, len_new(stock) + 1);
		return (gnl);
	}
	else
	{
		gnl = ft_strdup(stock);
		stock = NULL;
	}
	return (gnl);
}

char	*get_next_line(int fd)
{
	int			t;
	char		*gnl;
	char		*temp;
	char		*baf;
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	baf = gc(BUFFER_SIZE + 1, 1, 0);
	if (!baf)
		return (NULL);
	t = BUFFER_SIZE;
	while (t > 0 && !ft_strchr(stock, '\n'))
	{
		t = read(fd, baf, BUFFER_SIZE);
		if (t <= 0)
			break ;
		baf[t] = '\0';
		temp = ft_strjoin(stock, baf);
		stock = temp;
	}
	gnl = stop_at_nel(stock);
	stock = stock_str(stock);
	return (gnl);
}
