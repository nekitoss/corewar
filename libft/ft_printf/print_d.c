/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:35:46 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/19 17:32:39 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		flags(t_format *list)
{
	if (list->plus)
		list->space = 0;
	if (list->width < 0)
	{
		list->width *= -1;
		list->sign = '-';
	}
	if (list->sign == '-' || list->precision > -1)
		list->nul = 0;
}

static intmax_t	find_n(t_format *list, va_list *ar)
{
	intmax_t	i;

	if ((list->modifier == 'l' && list->mod_count == 2) ||
		(list->modifier == 'l' && (list->type == 'I' || list->type == 'D')))
		i = va_arg(*ar, long long int);
	else if ((list->type == 'D' || list->type == 'I') ||
			(list->modifier == 'l' && list->mod_count != 2))
		i = va_arg(*ar, long int);
	else if (list->modifier == 'j')
		i = va_arg(*ar, intmax_t);
	else if (list->modifier == 'z')
		i = va_arg(*ar, size_t);
	else if (list->modifier == 'h')
		i = (short int)va_arg(*ar, int);
	else
		i = va_arg(*ar, int);
	flags(list);
	return (i);
}

static char		*print_d_2(t_format *list, char *s)
{
	char		*c;
	int			i;
	int			j;
	char		*sign;

	j = 1;
	if (list->precision <= (int)ft_strlen(s))
		c = ft_alloc(2);
	else
	{
		c = ft_alloc(list->precision - (int)ft_strlen(s) + 2);
		i = list->precision + 1;
		while (--i > (int)ft_strlen(s))
			c[j++] = '0';
	}
	c[0] = list->plus ? '+' : ' ';
	sign = ft_strjoin(c, s);
	free(s);
	return (sign);
}

static char		*print_d_3(t_format *list, char *s)
{
	char		*c;
	int			i;
	int			j;
	char		*sign;

	j = 1;
	c = ft_alloc(list->precision - (int)ft_strlen(s));
	ft_memset(c, '\0', list->precision - (int)ft_strlen(s));
	c[0] = s[0];
	ft_memmove(s, s + 1, ft_strlen(s) - 1);
	s[ft_strlen(s) - 1] = '\0';
	i = list->precision + 1;
	while (--i > (int)ft_strlen(s))
		c[j++] = '0';
	sign = ft_strjoin(c, s);
	free(s);
	return (sign);
}

void			print_d(va_list *ar, t_format *list)
{
	intmax_t	i;
	char		*s;
	char		*sign;
	int			j;

	j = 1;
	i = typecheck(find_n(list, ar), list);
	if (list->modifier == 'b')
		s = ft_itoa_ubase(i, 2, 0);
	else
		s = ft_itoa(i);
	if (i > -1 && (list->plus || list->space))
		sign = print_d_2(list, s);
	else if (s[0] == '-' && list->precision > (int)ft_strlen(s) - 1)
		sign = print_d_3(list, s);
	else
	{
		sign = ft_strdup(s);
		if (s[0] == '0')
			j = 0;
		free(s);
	}
	if (list->precision == 0 && j == 0)
		sign = fta(sign, 1);
	arrs(list, sign);
}
