/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:08:19 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 17:30:55 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				parse_star(char *str)
{
	while (!is_convers(*str, "sSpdDioOuUxXcC"))
	{
		if (*str == '*')
			return (666);
		str++;
	}
	return (0);
}

char			*ft_uitoa(uintmax_t value)
{
	int			i;
	uintmax_t	n;
	char		*s;
	char		*h;

	h = "0123456789";
	i = 1;
	n = value;
	while (n /= 10)
		i++;
	if ((s = (char*)malloc(sizeof(char) * i + 1)) == 0)
		return (NULL);
	s[i] = 0;
	if (value == 0)
		s[0] = '0';
	n = value;
	while (n)
	{
		s[--i] = h[n % 10];
		n /= 10;
	}
	return (s);
}
