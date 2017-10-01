/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 13:10:43 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/17 12:41:40 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_symb(intmax_t n)
{
	int len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	if (n == 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	fill(char *res, intmax_t n, int len)
{
	int		j;

	j = 0;
	if (n < 0)
	{
		res[j] = '-';
		j++;
		n *= -1;
	}
	while (len >= j)
	{
		res[len] = n % 10 + '0';
		len--;
		n /= 10;
	}
}

char		*ft_itoa(intmax_t n)
{
	int			len;
	char		*res;

	if (n == INTMAX_MIN)
	{
		len = num_of_symb(n / 10) + 1;
		res = malloc(len + 1);
		res[len] = '\0';
		res[len - 1] = (n % 10) * -1 + '0';
		n /= 10;
		fill(res, n, len - 2);
	}
	else
	{
		len = num_of_symb(n);
		res = malloc(len + 1);
		res[len] = '\0';
		fill(res, n, len - 1);
	}
	return (res);
}
