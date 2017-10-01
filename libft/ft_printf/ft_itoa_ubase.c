/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ubase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:24:48 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/17 17:08:37 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(uintmax_t i, int base)
{
	int		len;

	len = 0;
	if (i == 0)
		len++;
	while (i)
	{
		i /= base;
		len++;
	}
	return (len);
}

static void	fill(char *arr, uintmax_t i, int base, int flag)
{
	char	*s;
	int		len;

	if (flag)
		s = "0123456789ABCDEF";
	else
		s = "0123456789abcdef";
	len = ft_len(i, base) - 1;
	while (len >= 0)
	{
		arr[len] = s[i % base];
		len--;
		i /= base;
	}
}

char		*ft_itoa_ubase(uintmax_t i, int base, int flag)
{
	char	*arr;
	int		len;

	len = ft_len(i, base);
	arr = malloc(len + 1);
	arr[len] = '\0';
	fill(arr, i, base, flag);
	return (arr);
}
