/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 17:32:58 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 16:16:03 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(intmax_t value)
{
	int			i;
	intmax_t	n;
	char		*s;
	char		*h;

	h = "0123456789";
	i = (value < 0) ? 2 : 1;
	n = value;
	while (n /= 10)
		i++;
	if ((s = (char*)malloc(sizeof(char) * i + 1)) == 0)
		return (NULL);
	s[i] = 0;
	if (value < 0)
		s[0] = '-';
	if (value == 0)
		s[0] = '0';
	n = value;
	while (n)
	{
		s[--i] = h[(n < 0) ? -(n % 10) : n % 10];
		n /= 10;
	}
	return (s);
}
