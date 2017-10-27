/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_for_ss.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:46:13 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 18:11:11 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			wchar_strlen(wchar_t *s)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char		*make_norm_str(wchar_t *str)
{
	char	*s;
	int		i;
	int		a;

	i = -1;
	a = -1;
	if (!str)
		return (NULL);
	i = wchar_strlen(str) + 1;
	if (!(s = (char*)malloc((size_t)i)))
		return (NULL);
	while (++a < i)
		s[a] = (char)str[a];
	return (s);
}

int			app_flags_ss(int size, char *strn, t_print *ls)
{
	int		size1;
	char	*fl;

	fl = ls->flags;
	size1 = (int)ft_strlen(strn);
	if (fl[0] == '1')
	{
		if (size < size1)
			strn = ft_strjoin(&strn[size1 - size], newstr(size1 - size, ' '));
	}
	if (fl[2] == '1' && fl[0] != '1')
	{
		size1 = 0;
		if (ls->precision < ls->width)
			while (strn[size1] == ' ')
				strn[size1++] = '0';
	}
	ft_putstr(strn);
	return ((int)ft_strlen(strn));
}

int			apply_w_p_ss(t_print *lst, char *st)
{
	int		size_n;
	char	*str;
	int		size_m;

	size_m = 0;
	size_n = (int)ft_strlen(st);
	if (lst->precision < size_n && lst->prec_fl == 1)
	{
		str = ft_strnew((size_t)lst->precision);
		while (size_m < lst->precision)
		{
			str[size_m] = st[size_m];
			size_m++;
		}
	}
	else
		str = st;
	size_n = (int)ft_strlen(str);
	if (lst->width > size_n)
		str = ft_strjoin(newstr(lst->width - size_n, ' '), str);
	return (app_flags_ss(size_n, str, lst));
}

int			next_step_for_ss(t_print *list, va_list ptr)
{
	wchar_t	*str1;
	char	*str;

	str = 0;
	str1 = 0;
	if ((list->convers == 's' && list->size == 2) || list->convers == 'S')
	{
		str1 = va_arg(ptr, wchar_t*);
		str = make_norm_str(str1);
	}
	else
		str = va_arg(ptr, char*);
	if (str == 0)
	{
		if (list->prec_fl == 0)
		{
			ft_putstr("(null)");
			return (6);
		}
		str = "(null)";
	}
	return (apply_w_p_ss(list, str));
}
