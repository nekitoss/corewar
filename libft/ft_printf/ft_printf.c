/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 12:45:43 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/17 13:10:34 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			g_len;

void		form_init(t_format *list)
{
	list->flag = 0;
	list->width = 0;
	list->precision = -1;
	list->modifier = 0;
	list->mod_count = 0;
	list->type = 0;
	list->sign = 0;
	list->plus = 0;
	list->space = 0;
	list->nul = 0;
}

void		compare(va_list *ar, t_format *list)
{
	if (list->type == 's' || list->type == 'S')
		print_s(ar, list);
	else if (list->type == 'd' || list->type == 'D' || list->type == 'i')
		print_d(ar, list);
	else if (list->type == 'o' || list->type == 'O')
		print_o(ar, list);
	else if (list->type == 'u' || list->type == 'U')
		print_u(ar, list);
	else if (list->type == 'x' || list->type == 'X')
		print_x(ar, list);
	else if (list->type == 'c' || list->type == 'C')
		print_c(ar, list);
	else if (list->type == 'p')
		print_p(ar, list);
	else if (list->type == '%')
		print_per(list);
	else if (list->type == 'f' || list->type == 'F')
		print_f(ar, list);
}

static int	check(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i' ||
		c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C' || c == 'f' || c == 'F' ||
		c == '%' || c == '#' || c == '0' || c == '-' || c == '+' || c == ' ' ||
		c == '*' || (c >= '0' && c <= '9') || c == '.' || c == 'h' ||
		c == 'l' || c == 'j' || c == 'z' || c == 'L' || c == 'b')
		return (1);
	else
		return (0);
}

char		*fill_list(char *format, va_list *ar, t_format *list)
{
	format += 1;
	while (!is_type(*format) && check(*format))
	{
		if (is_flag(*format))
			format = do_flag(format, list);
		else if (is_width(*format))
			format = do_width(format, list, ar);
		else if (is_precision(*format))
			format = do_presicion(++format, list, ar);
		else if (is_modifier(*format))
			format = do_modifier(format, list);
		format += 1;
	}
	do_type(*format, list);
	return (format);
}

int			ft_printf(const char *format, ...)
{
	t_format	list;
	va_list		ar;

	form_init(&list);
	va_start(ar, format);
	g_len = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format = fill_list((char*)format, &ar, &list);
			if (list.type != 0)
				compare(&ar, &list);
			else
				format = not_valid(&list, (char*)format);
			form_init(&list);
		}
		else
			ft_putchar(*format);
		format += 1;
	}
	va_end(ar);
	return (g_len);
}
