/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_for_xx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:48:53 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 18:50:23 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			app_flags_xx(int size, char *strn, t_print *ls, int size2)
{
	int		size1;

	size1 = (int)ft_strlen(strn);
	if (ls->flags[3] == '1' && ((ls->flags[2] != '1') || (ls->flags[2] == '1'
					&& ls->flags[0] == '1')))
	{
		if ((size < ls->width || size < ls->precision))
		{
			while (!ft_isdigit(strn[size2]))
				size2++;
			if (ls->convers == 'x')
				strn[--size2] = 'x';
			else
				strn[--size] = 'X';
			strn[--size2] = '0';
			size += 2;
		}
		else if (ft_atoi(strn) != 0)
			strn = (ls->convers == 'x') ? ft_strjoin("0x", strn) :
				ft_strjoin("0X", strn);
	}
	return (app_flags_xx2(size, strn, ls, size1));
}

int			app_flags_xx2(int size, char *strn, t_print *ls, int size1)
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
		if (fl[3] == '1')
		{
			if (ls->convers == 'x')
				strn[1] = 'x';
			else
				strn[1] = 'X';
		}
	}
	ft_putstr(strn);
	return ((int)ft_strlen(strn));
}

int			apply_w_p_xx(t_print *lst, char *strnum)
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
		if (lst->width == 0)
			str[ft_strlen(str) - 1] = '\0';
		ft_putstr(str);
		return ((int)ft_strlen(str));
	}
	return (app_flags_xx(size_n, str, lst, 0));
}

int			next_step_for_x(t_print *list, va_list ptr)
{
	char	*str;
	char	c;

	c = list->convers;
	if (c == 'X' && list->size == 1)
		str = ft_itoa_base(va_arg(ptr, unsigned long long int), 16, 1);
	else if (c == 'X' && list->size == 2)
		str = ft_itoa_base(va_arg(ptr, unsigned long int), 16, 1);
	else if (c == 'X' && list->size == 3)
		str = ft_itoa_base((unsigned short int)va_arg(ptr, unsigned int),
				16, 1);
	else if (c == 'X' && list->size == 4)
		str = ft_itoa_base((unsigned char)va_arg(ptr, unsigned int), 16, 1);
	else if (c == 'X' && list->size == 5)
		str = ft_itoa_base(va_arg(ptr, uintmax_t), 16, 1);
	else if (c == 'X' && list->size == 6)
		str = ft_itoa_base(va_arg(ptr, size_t), 16, 1);
	else
		str = ft_itoa_base(va_arg(ptr, unsigned int), 16, 1);
	return (apply_w_p_xx(list, str));
}

int			next_step_for_xx(t_print *list, va_list ptr)
{
	char	*str;
	char	c;

	c = list->convers;
	if (c == 'X')
		return (next_step_for_x(list, ptr));
	else
	{
		if (c == 'x' && list->size == 1)
			str = ft_itoa_base(va_arg(ptr, unsigned long long int), 16, 0);
		else if (c == 'x' && list->size == 2)
			str = ft_itoa_base(va_arg(ptr, unsigned long int), 16, 0);
		else if (c == 'x' && list->size == 3)
			str = ft_itoa_base((unsigned short int)va_arg(ptr, unsigned int),
					16, 0);
		else if (c == 'x' && list->size == 4)
			str = ft_itoa_base((unsigned char)va_arg(ptr, unsigned int), 16, 0);
		else if (c == 'x' && list->size == 5)
			str = ft_itoa_base(va_arg(ptr, uintmax_t), 16, 0);
		else if (c == 'x' && list->size == 6)
			str = ft_itoa_base(va_arg(ptr, size_t), 16, 0);
		else
			str = ft_itoa_base(va_arg(ptr, unsigned int), 16, 0);
	}
	return (apply_w_p_xx(list, str));
}
