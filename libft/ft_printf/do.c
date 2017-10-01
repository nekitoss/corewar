/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:16:03 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/30 16:18:43 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*do_flag(char *format, t_format *list)
{
	while (*format == '#' || *format == '0' || *format == '-' ||
			*format == '+' || *format == ' ')
	{
		if (*format == '#')
			list->flag = '#';
		if (*format == '0')
			list->nul = 1;
		if (*format == '-')
			list->sign = *format;
		if (*format == '+')
			list->plus = 1;
		if (*format == ' ')
			list->space = 1;
		format += 1;
	}
	return (format - 1);
}

char	*do_width(char *format, t_format *list, va_list *ar)
{
	int		i;
	char	*s;

	i = 0;
	if (format[i] == '*')
		list->width = zero(ar);
	else
	{
		while (format[i] >= '0' && format[i] <= '9')
			i++;
		s = ft_alloc(i + 1);
		i = 0;
		while (*format >= '0' && *format <= '9')
		{
			s[i++] = *format;
			format++;
		}
		list->width = ft_atoi(s);
		free(s);
		format -= 1;
	}
	return (format);
}

char	*do_presicion(char *format, t_format *list, va_list *ar)
{
	int		i;
	char	*s;

	i = 0;
	if (format[i] == '*')
		list->precision = zero(ar);
	else
	{
		while (format[i] >= '0' && format[i] <= '9')
			i++;
		s = ft_alloc(i + 1);
		i = 0;
		while (*format >= '0' && *format <= '9')
		{
			s[i++] = *format;
			format += 1;
		}
		list->precision = ft_atoi(s);
		free(s);
		format -= 1;
	}
	if (list->precision == -1)
		list->precision = 0;
	return (format);
}

char	*do_modifier(char *format, t_format *list)
{
	int		i;

	i = 0;
	while (format[i] == 'h' || format[i] == 'l' || format[i] == 'j' ||
		format[i] == 'j' || format[i] == 'L' || format[i] == 'z' ||
		format[i] == 'b')
		i++;
	if (i == 1)
	{
		list->mod_count = 1;
		if (list->modifier == *format)
			list->mod_count++;
		list->modifier = *format;
	}
	else
	{
		list->mod_count = 2;
		list->modifier = *format;
		format += 1;
	}
	return (format);
}

void	do_type(char c, t_format *list)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i' ||
		c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C' || c == 'f' || c == 'F' ||
		c == '%')
		list->type = c;
	else
		list->type = 0;
}
