/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:47:01 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/19 20:00:40 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			print(char *s, char *arr1, char *arr2, t_format *list)
{
	if (list->sign == '-')
	{
		print_str(arr2);
		print_str(s);
		print_str(arr1);
	}
	else
	{
		print_str(arr1);
		print_str(arr2);
		print_str(s);
	}
	free(arr1);
	free(arr2);
	free(s);
}

static void			check_print(t_format *list, char *arr1,
								char *arr2, char *num)
{
	char				*tmp;

	if (list->flag == '#')
	{
		if (list->nul != 0)
		{
			tmp = list->type == 'x' ? ft_strjoin("0x", arr1) :
					ft_strjoin("0X", arr1);
			print(num, tmp, arr2, list);
		}
		else
		{
			tmp = list->type == 'x' ? ft_strjoin("0x", arr2) :
					ft_strjoin("0X", arr2);
			print(num, arr1, tmp, list);
		}
	}
	else
		print(num, arr1, arr2, list);
}

static void			fill(int len, char *num, t_format *list)
{
	char				*arr1;
	char				*arr2;
	int					i;

	i = 0;
	list->nul = (list->precision != -1) ? 0 : list->nul;
	if (list->precision > len)
	{
		i = list->precision - len;
		arr2 = ft_alloc(i + 1);
		ft_memset(arr2, '0', i);
	}
	else
		arr2 = ft_alloc(1);
	i += (list->flag == '#') ? 2 : 0;
	if (list->width > 0 && list->width >
		(list->precision > len ? list->precision : len))
	{
		arr1 = ft_alloc(list->width - len - i + 1);
		ft_memset(arr1, ((list->nul) ? '0' : ' '), list->width - len - i);
	}
	else
		arr1 = ft_alloc(1);
	check_print(list, arr1, arr2, num);
}

static uintmax_t	find_n(t_format *list, va_list *ar)
{
	uintmax_t			i;

	if ((list->modifier == 'l' && list->mod_count == 2) ||
		(list->modifier == 'l' && list->type == 'U'))
		i = va_arg(*ar, unsigned long long int);
	else if (list->modifier == 'l' || list->type == 'U')
		i = va_arg(*ar, unsigned long int);
	else if (list->modifier == 'j')
		i = va_arg(*ar, uintmax_t);
	else if (list->modifier == 'z')
		i = va_arg(*ar, size_t);
	else if (list->modifier == 'h' && list->mod_count != 2)
		i = (unsigned short int)va_arg(*ar, unsigned int);
	else
		i = va_arg(*ar, unsigned int);
	return (i);
}

void				print_x(va_list *ar, t_format *list)
{
	int					len;
	char				*num;
	uintmax_t			i;
	unsigned long int	j;

	i = find_n(list, ar);
	if (list->modifier == 'h' && list->mod_count == 2)
	{
		j = i;
		if (list->type == 'x')
			j = (unsigned int)j;
		i = (unsigned char)j;
	}
	if (list->type == 'X')
		num = ft_itoa_ubase(i, 16, 1);
	else
		num = ft_itoa_ubase(i, 16, 0);
	if (list->precision == 0)
		ft_memset(num, '\0', ft_strlen(num));
	len = ft_strlen(num);
	if (i == 0 && list->flag == '#')
		list->flag = ' ';
	if (list->sign == '-')
		list->nul = 0;
	fill(len, num, list);
}
