/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:17:40 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/17 16:24:12 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		convert_count(wchar_t c)
{
	int		i;

	i = 0;
	if (c < (1 << 7))
		i = 1;
	else if (c < (1 << 11))
		i = 2;
	else if (c < (1 << 16))
		i = 3;
	else if (c < (1 << 21))
		i = 4;
	return (i - 1);
}