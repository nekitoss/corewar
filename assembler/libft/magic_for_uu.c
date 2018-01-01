/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_for_uu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:44:14 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 18:15:59 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			app_flags_uu(int size, char *strn, t_print *ls)
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
		if (ls->prec_fl == 0)
			while (!ft_isdigit(strn[size1]))
				strn[size1++] = '0';
	}
	ft_putstr(strn);
	return ((int)ft_strlen(strn));
}

int			apply_w_p_uu(t_print *lst, char *strnum)
{
	int		size_n;
	char	*str;

	if (lst->prec_fl == 1 && lst->precision == 0 && *strnum == '0')
		return (0);
	size_n = (int)ft_strlen(strnum);
	if (lst->precision > size_n)
		str = ft_strjoin(newstr(lst->precision - size_n, '0'), strnum);
	else
		str = strnum;
	size_n = (int)ft_strlen(str);
	if (lst->width > size_n)
		str = ft_strjoin(newstr(lst->width - size_n, ' '), str);
	return (app_flags_uu(size_n, str, lst));
}

int			next_step_for_uu(t_print *list, va_list ptr)
{
	char	*str;
	char	c;

	c = list->convers;
	if (c == 'u' && list->size == 1)
		str = ft_uitoa(va_arg(ptr, unsigned long long int));
	else if ((c == 'u' && list->size == 2) || c == 'U')
		str = ft_uitoa(va_arg(ptr, unsigned long int));
	else if (c == 'u' && list->size == 3)
		str = ft_uitoa((unsigned short int)va_arg(ptr, unsigned int));
	else if (c == 'u' && list->size == 4)
		str = ft_uitoa((unsigned char)va_arg(ptr, unsigned int));
	else if (c == 'u' && list->size == 5)
		str = ft_uitoa(va_arg(ptr, uintmax_t));
	else if (c == 'u' && list->size == 6)
		str = ft_uitoa(va_arg(ptr, size_t));
	else
		str = ft_uitoa(va_arg(ptr, unsigned int));
	return (apply_w_p_uu(list, str));
}
