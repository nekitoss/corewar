/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 17:36:45 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/19 16:59:34 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			g_len;

static void	print(char *s, wchar_t c, t_format *list)
{
	if (list->sign != '-')
	{
		print_str(s);
		convert(c, -1, 1);
	}
	else
	{
		convert(c, -1, 1);
		print_str(s);
	}
	free(s);
}

static void	check(t_format *list)
{
	if (list->width < 0)
	{
		list->width *= -1;
		list->sign = '-';
	}
	if (list->sign == '-')
		list->nul = 0;
}

static void	print_2(char *s, wchar_t c, t_format *list)
{
	if (list->sign != '-')
	{
		print_str(s);
		ft_putchar((char)c);
	}
	else
	{
		ft_putchar((char)c);
		print_str(s);
	}
	free(s);
}

void		print_c(va_list *ar, t_format *list)
{
	wchar_t	c;
	char	*s;
	int		i;

	c = va_arg(*ar, wchar_t);
	i = convert_count(c);
	check(list);
	if (list->type == 'c' && list->modifier != 'l')
		i++;
	else if (c == 0 && list->mod_count != 2 && list->modifier != 'h' &&
			list->type != 'C')
		g_len++;
	if (list->width > i)
	{
		s = ft_alloc(list->width - i + 1);
		list->nul == 1 ? ft_memset(s, '0', list->width - i) :
		ft_memset(s, ' ', list->width - i);
	}
	else
		s = ft_alloc(1);
	if ((list->type == 'c' && list->modifier != 'l') || (list->modifier == 'h'
		&& list->mod_count == 2 && c == 0) || (list->type == 'C' && c == 0))
		print_2(s, c, list);
	else
		print(s, c, list);
}
