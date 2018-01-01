/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_for_cc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:44:53 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 16:13:42 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr_my(char *str, size_t num, char st)
{
	while (num != 0)
	{
		if (*str == '?')
			write(1, &st, 1);
		else
			write(1, str, 1);
		str++;
		num--;
	}
}

int			app_flags_cc(int size, char *strn, t_print *ls, char st)
{
	char	*fl;

	fl = ls->flags;
	if (fl[0] == '1')
	{
		if (1 < size)
			strn = ft_strjoin(&strn[size - 1], newstr(size - 1, ' '));
	}
	if (fl[2] == '1' && fl[0] == ' ')
	{
		size--;
		while (--size >= 0)
			strn[size] = '0';
	}
	ft_putstr_my(strn, ft_strlen(strn), st);
	return ((int)ft_strlen(strn));
}

int			apply_w_p_cc(t_print *lst, char st)
{
	char	*str;
	int		size_n;

	str = ft_strnew(1);
	*str = '?';
	if (lst->width > 1)
		str = ft_strjoin(newstr(lst->width - 1, ' '), str);
	size_n = (int)ft_strlen(str);
	return (app_flags_cc(size_n, str, lst, st));
}

int			next_step_for_cc(t_print *list, va_list ptr)
{
	char	c;

	c = (char)va_arg(ptr, int);
	return (apply_w_p_cc(list, c));
}
