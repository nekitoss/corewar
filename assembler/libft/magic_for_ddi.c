/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_for_ddi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:43:22 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 17:41:33 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			app_flags_ddi(int size, char *strn, char l, t_print *ls)
{
	int		size1;

	size1 = (int)ft_strlen(strn);
	if (ls->flags[1] == '1' && l == '+')
	{
		if (size1 > size)
			strn[size1 - size - 1] = '+';
		else
			strn = ft_strjoin("+", strn);
		size++;
	}
	if (ls->flags[4] == '1' && ls->flags[1] != '1' && l != '-')
	{
		if (size1 > size)
			strn[size1 - size - 1] = ' ';
		else
			strn = ft_strjoin(" ", strn);
		size++;
	}
	return (app_flags_ddi2(size, strn, l, ls));
}

int			app_flags_ddi2(int size, char *strn, char l, t_print *ls)
{
	int		size1;

	size1 = (int)ft_strlen(strn);
	if (ls->flags[0] == '1')
	{
		if (size < size1)
			strn = ft_strjoin(&strn[size1 - size], newstr(size1 - size, ' '));
	}
	if (ls->flags[2] == '1' && ls->flags[0] == ' ')
	{
		size1 = 0;
		if (ls->prec_fl == 0)
		{
			if (l == '-')
				strn[size1++] = '-';
			else if (ls->flags[1] == '1' && l == '+')
				strn[size1++] = '+';
			while (!ft_isdigit(strn[size1]))
				strn[size1++] = '0';
			if (ls->flags[4] == '1' && l != '-' && ls->flags[1] != '1')
				strn[0] = ' ';
		}
	}
	ft_putstr(strn);
	return ((int)ft_strlen(strn));
}

int			apply_w_p_ddi(t_print *lst, char *strnum, char lb)
{
	int		size_n;
	char	*str;

	size_n = (int)ft_strlen(strnum);
	if (lb == '-')
		size_n--;
	if (lst->precision > size_n)
	{
		if (lb == '-')
		{
			strnum++;
			str = ft_strjoin(newstr(lst->precision - size_n + 1, '0'), strnum);
			str[0] = '-';
		}
		else
			str = ft_strjoin(newstr(lst->precision - size_n, '0'), strnum);
	}
	else
		str = strnum;
	return (apply_w_p_ddi2(lst, strnum, lb, str));
}

int			apply_w_p_ddi2(t_print *lst, char *strnum, char lb, char *str)
{
	int		size_n;

	size_n = (int)ft_strlen(str);
	if (lst->width > size_n)
		str = ft_strjoin(newstr(lst->width - size_n, ' '), str);
	if (ft_atoi(strnum) == 0 && lst->prec_fl == 1 && lst->precision == 0)
	{
		str[ft_strlen(str) - 1] = ' ';
		if (lst->width == 0)
			str[ft_strlen(str) - 1] = '\0';
		ft_putstr(str);
		return (int)ft_strlen(str);
	}
	return (app_flags_ddi(size_n, str, lb, lst));
}

int			next_step_for_ddi(t_print *list, va_list ptr)
{
	char	*str;
	char	l;

	l = '+';
	if ((list->convers == 'd' || list->convers == 'i') && list->size == 1)
		str = ft_itoa(va_arg(ptr, long long int));
	else if (((list->convers == 'd' || list->convers == 'i') && list->size == 2)
			|| list->convers == 'D')
		str = ft_itoa(va_arg(ptr, long int));
	else if ((list->convers == 'd' || list->convers == 'i') && list->size == 3)
		str = ft_itoa((short int)va_arg(ptr, int));
	else if ((list->convers == 'd' || list->convers == 'i') && list->size == 4)
		str = ft_itoa((char)va_arg(ptr, int));
	else if ((list->convers == 'd' || list->convers == 'i') && list->size == 5)
		str = ft_itoa(va_arg(ptr, intmax_t));
	else if ((list->convers == 'd' || list->convers == 'i') && list->size == 6)
		str = ft_itoa(va_arg(ptr, size_t));
	else
		str = ft_itoa(va_arg(ptr, int));
	if (str[0] == '-')
		l = '-';
	return (apply_w_p_ddi(list, str, l));
}
