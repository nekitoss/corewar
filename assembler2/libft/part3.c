/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:35:34 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 17:30:22 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			parse_width(char *str)
{
	char	*s;
	char	*c;

	c = "0";
	while (!is_convers(*str, "sSpdDioOuUxXcC"))
	{
		if (*str == '.')
			while (ft_isdigit(*(++str)))
				;
		else if (ft_isdigit(*str) && !is_convers(*str, "sSpdDioOuUxXcC"))
		{
			s = ft_strnew(10);
			c = s;
			while (ft_isdigit(*(str)))
				*s++ = *str++;
		}
		else
			str++;
	}
	return (ft_atoi(c));
}

int			parse_precision(char *str, t_print **l)
{
	char	*st;
	char	*c;

	c = "0";
	while (!is_convers(*str, "sSpdDioOuUxXcC"))
	{
		if (*str == '.')
		{
			(*l)->prec_fl = 1;
			str++;
			st = newstr(10, ' ');
			c = st;
			while (ft_isdigit(*str))
				*st++ = *str++;
		}
		else
			str++;
	}
	return (ft_atoi(c));
}

int			parse_size(char *str)
{
	int		ret_fl;

	ret_fl = 0;
	while (!is_convers(*str, "sSpdDioOuUxXcC"))
	{
		if (*str == 'l' && *(str + 1) == 'l')
			ret_fl = 1;
		if (*(str - 1) != 'l' && *str == 'l' && *(str + 1) != 'l')
			ret_fl = 2;
		if (*(str - 1) != 'h' && *str == 'h' && *(str + 1) != 'h')
			ret_fl = 3;
		if (*str == 'h' && *(str + 1) == 'h')
			ret_fl = 4;
		if (*str == 'j')
			ret_fl = 5;
		if (*str == 'z')
			ret_fl = 6;
		str++;
	}
	return (ret_fl);
}

char		parse_convers(char *str)
{
	while (*str && *str != '\0' && is_convers(*str, "sSpdDioOuUxXcC") == 0)
		str++;
	return (is_convers(*str, "sSpdDioOuUxXcC"));
}

t_print		*do_parse(char **str)
{
	t_print	*ret_lst;
	char	*st;

	st = *str;
	ret_lst = new_struc();
	ret_lst->flags = parse_flags(st);
	ret_lst->width = parse_width(st);
	ret_lst->precision = parse_precision(st, &ret_lst);
	ret_lst->size = parse_size(st);
	ret_lst->convers = parse_convers(st);
	ret_lst->star = parse_star(st);
	while (is_convers(**str, "sSpdDioOuUxXcC") == 0)
		(*str)++;
	(*str)++;
	pass_some(str);
	return (ret_lst);
}
