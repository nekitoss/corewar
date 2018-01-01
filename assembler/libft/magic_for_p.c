/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_for_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:49:35 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 16:41:20 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			app_flags_p(int size, char *strn, t_print *ls)
{
	int		size1;

	size1 = (int)ft_strlen(strn);
	if (ls->flags[0] == '1')
	{
		if (size < size1)
			strn = ft_strjoin(&strn[size1 - size], newstr(size1 - size, ' '));
	}
	if (ls->flags[2] == '1' && ls->flags[0] != '1')
	{
		size1 = 0;
		if (ls->prec_fl == 0)
			while (!ft_isdigit(strn[size1]))
				strn[size1++] = '0';
	}
	ft_putstr(strn);
	return ((int)ft_strlen(strn));
}

int			next_step_for_p(t_print *list, va_list ptr)
{
	char	*str;
	int		size_n;

	str = ft_itoa_base(va_arg(ptr, unsigned long int), 16, 0);
	if (list->precision == 0 && list->prec_fl == 1 && *str == '0' &&
			*(str + 1) == '\0')
	{
		ft_putstr("0x");
		return (2);
	}
	size_n = (int)ft_strlen(str);
	if (list->precision > size_n)
		str = ft_strjoin(newstr(list->precision - size_n, '0'), str);
	size_n = (int)ft_strlen(str);
	if (list->width > size_n)
		str = ft_strjoin(newstr(list->width - size_n, ' '), str);
	return (next_step_for_p2(list, str, size_n));
}

int			next_step_for_p2(t_print *list, char *str, int sn)
{
	int		s2;

	s2 = 0;
	if (sn < list->width || sn < list->precision)
	{
		while (!ft_isdigit(str[s2]))
			s2++;
		str[--s2] = 'x';
		if (s2 == 0)
			str = ft_strjoin("0", str);
		else
			str[--s2] = '0';
	}
	else
		str = ft_strjoin("0x", str);
	sn += 2;
	return (app_flags_p(sn, str, list));
}
