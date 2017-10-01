/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:57:33 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/30 16:35:04 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		order(char *st, t_format *list, char *s, int j)
{
	int		i;
	int		l;

	i = 0;
	l = 1;
	while (j > 0)
	{
		if (list->type == 'S' || list->modifier == 'l')
			l = convert(((wint_t*)st)[i], j, 1);
		else
			l = convert((wint_t)st[i], j, 1);
		j -= l;
		i++;
	}
	if (list->sign == '-' && s[0] != '\0')
		print_str(s);
	if (s[0] != '\0')
		free(s);
}

static char		*check_null(t_format *list, char *str)
{
	if (list->precision == 0)
		str = "\0";
	if (str == NULL)
		str = "(null)";
	if (!(ft_strcmp(str, "(null)")))
	{
		list->type = 's';
		list->modifier = 0;
	}
	return (str);
}

static int		do_wide(char *str, t_format *list)
{
	int k;
	int m;
	int j;
	int z;
	int i;

	k = (int)ft_wcslen((wchar_t *)str) + 1;
	i = 0;
	j = 0;
	while (--k > 0)
	{
		m = convert(((wint_t *)str)[j++], 100, 0);
		i += m;
	}
	i = (list->precision > -1) ? list->precision : i;
	j = (int)ft_wcslen((wchar_t *)str) + 1;
	k = 0;
	z = i;
	while (--j > 0 && z > 0)
	{
		m = convert(((wint_t *)str)[k++], z, 0);
		i = (z - m < 0) ? (i - z) : i;
		z -= m;
	}
	return (i);
}

void			print_s(va_list *ar, t_format *list)
{
	char	*s;
	char	*str;
	int		i;

	str = va_arg(*ar, char*);
	str = check_null(list, str);
	if (list->type == 'S' || list->modifier == 'l')
		i = do_wide(str, list);
	else
		i = ((list->precision < (int)ft_strlen(str)) &&
			(list->precision > -1)) ? list->precision : (int)ft_strlen(str);
	if (!(ft_strcmp(str, "")))
		i = 0;
	if (list->sign == '-')
		list->nul = 0;
	s = "\0";
	if (!(i >= list->width))
	{
		s = ft_alloc(list->width - i + 1);
		list->nul ? ft_memset(s, '0', list->width - i) :
			ft_memset(s, ' ', list->width - i);
	}
	if (s[0] != '\0' && list->sign != '-')
		print_str(s);
	order(str, list, s, i);
}
