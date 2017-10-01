/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:22:02 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/19 18:51:44 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			print(t_format *list, char *nuls, char *str, char *spaces)
{
	if (list->sign == '-')
	{
		print_str("0x");
		print_str(nuls);
		print_str(str);
		print_str(spaces);
	}
	else if (ft_strlen(spaces) && spaces[0] == '0')
	{
		print_str("0x");
		print_str(spaces);
		print_str(nuls);
		print_str(str);
	}
	else
	{
		print_str(spaces);
		print_str("0x");
		print_str(nuls);
		print_str(str);
	}
	free(str);
	free(spaces);
	free(nuls);
}

static char			*find_n(t_format *list, va_list *ar, int *c)
{
	uintmax_t		i;
	char			*str;

	i = (uintmax_t)va_arg(*ar, void *);
	if (list->precision != -1)
		list->nul = 0;
	if (i == 0 && list->precision == 0)
		str = ft_alloc(1);
	else
		str = ft_itoa_ubase(i, 16, 0);
	*c = (int)ft_strlen(str) > list->precision ?
		(int)ft_strlen(str) : list->precision;
	return (str);
}

void				print_p(va_list *ar, t_format *list)
{
	char			*str;
	int				c;
	char			*spaces;
	int				j;
	char			*nuls;

	j = 0;
	str = find_n(list, ar, &c);
	if (list->width - c - 2 > 0)
		spaces = ft_alloc(list->width - c - 1);
	else
		spaces = ft_alloc(1);
	while (list->width - c - 2 > 0)
	{
		list->width -= 1;
		spaces[j++] = (list->nul) ? '0' : ' ';
	}
	if (list->precision - (int)ft_strlen(str) > 0)
		nuls = ft_alloc(list->precision - (int)ft_strlen(str) + 1);
	else
		nuls = ft_alloc(1);
	j = 0;
	while ((list->precision--) - (int)ft_strlen(str) > 0)
		nuls[j++] = '0';
	print(list, nuls, str, spaces);
}
