/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:13:31 by jmilhas           #+#    #+#             */
/*   Updated: 2022/03/02 23:11:02 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdarg.h>

static int	ft_get_full_len(va_list *args, const char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == 's')
		{
			len += ft_strlen(va_arg(*args, char *));
			i++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

static char	*ft_complet_join(va_list *args, const char *str, char *join)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == 's')
		{
			tmp = va_arg(*args, char *);
			if (tmp)
				ft_strcat(join, tmp);
			i++;
		}
		else
			ft_strncat(join, str + i, 1);
		i++;
	}
	return (join);
}

/* @function join str and add va_list %s */
/* @exemple ft_join("%s | %s", arg1, arg2); */
/* @arg1 const char * str */
/* @arg2 .. */
/* @return (join) */
char	*ft_join(const char *str, ...)
{
	va_list	args;
	char	*join;
	int		len;

	if (!str)
		return (NULL);
	va_start(args, str);
	len = ft_get_full_len(&args, str);
	join = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	va_end(args);
	va_start(args, str);
	ft_complet_join(&args, str, join);
	va_end(args);
	return (join);
}
