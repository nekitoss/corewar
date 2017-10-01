/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_per.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:55:09 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/19 18:55:31 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check(t_format *list)
{
	if (list->sign == '-')
		list->nul = 0;
}

void		print_per(t_format *list)
{
	char	*s;
	char	c;

	check(list);
	if (list->width > 1)
	{
		s = malloc(list->width);
		c = list->nul ? '0' : ' ';
		ft_memset(s, c, list->width - 1);
		s[list->width - 1] = '\0';
		if (list->sign == '-')
		{
			print_str("%");
			print_str(s);
		}
		else
		{
			print_str(s);
			print_str("%");
		}
		free(s);
	}
	else
		print_str("%");
}
