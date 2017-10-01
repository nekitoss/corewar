/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:52:19 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/30 16:42:32 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*fit(char *s1, char *s2)
{
	char		*s;
	int			i;
	char		*arr;

	s = ft_strjoin(s1, s2);
	i = ft_strlen(s) - 1;
	free(s1);
	if (s[i] >= '5')
		while (s[--i] == '9' && i >= 0)
			s[i] = '0';
	if (s[i] == '.')
		i--;
	while (s[i] == '9' && i >= 0)
		s[i--] = '0';
	if (i >= 0)
		s[i] += 1;
	else
	{
		arr = ft_strjoin("1", s);
		s = arr;
	}
	s[ft_strlen(s) - 1] = '\0';
	return (s);
}

static char	*make_str(long double ld, t_format *list)
{
	char		*first;
	char		*second;
	intmax_t	i;
	int			j;
	intmax_t	tmp;

	j = 0;
	i = ld;
	first = ft_itoa(i);
	second = malloc(100);
	ld -= i;
	if (list->precision != 0)
		second[j++] = '.';
	if (list->precision == -1)
		list->precision = 6;
	else
		list->nul = 0;
	while (list->precision-- + 1)
	{
		ld *= 10;
		tmp = ld;
		second[j++] = tmp % 10 + '0';
	}
	second[j] = '\0';
	return (fit(first, second));
}

static void	print_2(t_format *list, char *s, char *symb)
{
	if (list->sign == '-')
	{
		print_str(s);
		print_str(symb);
	}
	else
	{
		print_str(symb);
		print_str(s);
	}
	free(symb);
}

static void	print(char *s, t_format *list, char *arr)
{
	char		*rez;
	char		*symb;
	char		c;

	if (list->sign == '-')
		list->nul = 0;
	if (!list->nul && arr[0] != '-')
	{
		rez = ft_strjoin(arr, s);
		s = rez;
	}
	if (list->width > (int)ft_strlen(s))
	{
		symb = malloc(list->width - ft_strlen(s) + 1);
		symb[list->width - ft_strlen(s)] = '\0';
		c = list->nul ? '0' : ' ';
		ft_memset(symb, c, list->width - ft_strlen(s));
		if ((arr[0] == '+' || arr[0] == ' ') && list->nul)
			symb[0] = arr[0];
	}
	else
		symb = ft_alloc(1);
	print_2(list, s, symb);
}

void		print_f(va_list *ar, t_format *list)
{
	long double	ld;
	char		*s;
	char		*tmp;
	char		*arr;

	if (list->modifier == 'L')
		ld = va_arg(*ar, long double);
	else
		ld = va_arg(*ar, double);
	if (ld < 0)
	{
		ld *= -1;
		arr = "-";
	}
	else
		arr = "\0";
	s = make_str(ld, list);
	if (arr[0] == '-')
	{
		tmp = ft_strjoin("-", s);
		s = tmp;
	}
	else if (arr[0] != '-' && (list->plus || list->space))
		arr = list->plus ? "+" : " ";
	print(s, list, arr);
}
