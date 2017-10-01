/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:30:32 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/19 19:40:29 by rhulam           ###   ########.fr       */
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
	if (arr1[1] != '\0')
		free(arr1);
	if (arr2[1] != '\0')
		free(arr2);
	free(s);
}

static void			fill(int len, char *num, t_format *list)
{
	char			*arr1;
	char			*arr2;
	int				i;

	i = 0;
	arr1 = "\0";
	arr2 = "\0";
	if (list->precision != -1)
		list->nul = 0;
	if (list->precision > len)
	{
		i = list->precision - len;
		arr2 = ft_alloc(i + 1);
		ft_memset(arr2, '0', i);
	}
	if (list->width > 0 && list->width > list->precision && list->width > len)
	{
		arr1 = ft_alloc(list->width - len - i + 1);
		if (list->nul)
			ft_memset(arr1, '0', list->width - len - i);
		else
			ft_memset(arr1, ' ', list->width - len - i);
	}
	print(num, arr1, arr2, list);
}

static uintmax_t	find_n(t_format *list, va_list *ar)
{
	uintmax_t		i;

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
		i = (unsigned short)va_arg(*ar, unsigned int);
	else
		i = va_arg(*ar, unsigned int);
	return (i);
}

void				print_u(va_list *ar, t_format *list)
{
	int				len;
	char			*num;
	uintmax_t		i;
	unsigned int	j;

	i = find_n(list, ar);
	if (list->modifier == 'h' && list->mod_count == 2 && list->type != 'U')
	{
		j = i;
		i = (unsigned char)((unsigned int)j);
	}
	num = ft_itoa_ubase(i, 10, 0);
	if (i == 0 && list->precision == 0)
	{
		free(num);
		num = malloc(1);
		num[0] = '\0';
	}
	len = ft_strlen(num);
	fill(len, num, list);
}
