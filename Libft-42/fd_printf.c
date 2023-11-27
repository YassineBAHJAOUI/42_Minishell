/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:44:40 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 16:44:41 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	fd_printf(int fd, const char *fmt, ...)
{
	int		i;
	va_list	s;

	i = -1;
	va_start(s, fmt);
	while (fmt[++i])
	{
		(fmt[i] != '%') && (i += 0, write(fd, &fmt[i], 1));
		if (fmt[i] == '%' && fmt[i + 1])
		{
			if (fmt[i + 1] == 's')
				ft_putstr_fd(va_arg(s, char *), fd);
			else if (fmt[i + 1] == 'd')
				ft_putnbr_fd(va_arg(s, int), fd);
			else
				write(fd, &fmt[i + 1], 1);
			i++;
		}
	}
}
