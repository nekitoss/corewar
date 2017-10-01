/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_valid_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:03:45 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/17 13:12:17 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*not_valid(t_format *list, char *format)
{
	if (list->sign == '-')
	{
		ft_putchar(*format);
		format++;
	}
	while (list->width - 1 > 0)
	{
		if (list->nul)
			ft_putchar('0');
		else
			ft_putchar(' ');
		list->width -= 1;
	}
	format -= 1;
	return (format);
}
