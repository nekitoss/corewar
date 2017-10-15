/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_for_oo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:48:20 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 18:01:21 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			app_flags_oo(int size, char *strn, t_print *ls)
{
	int		size1;
	int		size2;
	char	*fl;

	fl = ls->flags;
	size1 = (int)ft_strlen(strn);
	if (fl[3] == '1' && ((ls->prec_fl == 1 && ls->precision == 0)
				|| ls->prec_fl == 0))
	{
		if ((size < ls->width || size < ls->precision))
		{
			size2 = 0;
			while (!ft_isdigit(strn[size2]))
				size2++;
			strn[--size2] = '0';
			size++;
		}
		else if (ft_atoi(strn) != 0)
			strn = ft_strjoin("0", strn);
	}
	return (app_flags_oo2(size, strn, ls, size1));
}

int			app_flags_oo2(int size, char *strn, t_print *ls, int size1)
{
	char	*fl;

	fl = ls->flags;
	if (fl[0] == '1')
	{
		if (size < size1)
			strn = ft_strjoin(&strn[size1 - size], newstr(size1 - size, ' '));
	}
	if (fl[2] == '1' && fl[0] != '1')
	{
		size1 = 0;
		if (ls->prec_fl == 0)
			while (!ft_isdigit(strn[size1]))
				strn[size1++] = '0';
	}
	ft_putstr(strn);
	return (int)ft_strlen(strn);
}

int			apply_w_p_oo(t_print *lst, char *strnum)
{
	int		size_n;
	char	*str;

	size_n = (int)ft_strlen(strnum);
	if (lst->precision > size_n)
		str = ft_strjoin(newstr(lst->precision - size_n, '0'), strnum);
	else
		str = strnum;
	size_n = (int)ft_strlen(str);
	if (lst->width > size_n)
		str = ft_strjoin(newstr(lst->width - size_n, ' '), str);
	if (ft_atoi(strnum) == 0 && lst->prec_fl == 1 && lst->precision == 0)
	{
		str[ft_strlen(str) - 1] = ' ';
		if (lst->flags[3] == '1')
			str[ft_strlen(str) - 1] = '0';
		else if (lst->width == 0)
			str[ft_strlen(str) - 1] = '\0';
		ft_putstr(str);
		return ((int)ft_strlen(str));
	}
	return (app_flags_oo(size_n, str, lst));
}

int			next_step_for_oo(t_print *list, va_list ptr)
{
	char	*str;
	char	c;

	c = list->convers;
	if (c == 'o' && list->size == 1)
		str = ft_itoa_base(va_arg(ptr, unsigned long long int), 8, 0);
	else if ((c == 'o' && list->size == 2) || c == 'O')
		str = ft_itoa_base(va_arg(ptr, unsigned long int), 8, 0);
	else if (c == 'o' && list->size == 3)
		str = ft_itoa_base((unsigned short int)va_arg(ptr, unsigned int), 8, 0);
	else if (c == 'o' && list->size == 4)
		str = ft_itoa_base((unsigned char)va_arg(ptr, unsigned int), 8, 0);
	else if (c == 'o' && list->size == 5)
		str = ft_itoa_base(va_arg(ptr, uintmax_t), 8, 0);
	else if (c == 'o' && list->size == 6)
		str = ft_itoa_base(va_arg(ptr, size_t), 8, 0);
	else
		str = ft_itoa_base(va_arg(ptr, unsigned int), 8, 0);
	return (apply_w_p_oo(list, str));
}
