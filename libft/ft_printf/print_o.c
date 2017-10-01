/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:57:33 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/19 18:21:07 by rhulam           ###   ########.fr       */
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

static char			*fill_1(t_format *list, int len, int i)
{
	char *arr1;

	if (list->precision != -1)
		list->nul = 0;
	if (list->width < len && list->precision < len)
	{
		list->width = 0;
		list->precision = -1;
	}
	if (list->width > 0 && list->width > list->precision)
	{
		arr1 = ft_alloc(list->width - len - i + 1);
		if (list->nul)
			ft_memset(arr1, '0', list->width - len - i);
		else
			ft_memset(arr1, ' ', list->width - len - i);
	}
	else
		arr1 = ft_alloc(1);
	return (arr1);
}

static void			fill(int len, char *num, t_format *list)
{
	char			*arr1;
	char			*arr2;
	char			*tmp;
	int				i;

	i = 0;
	if (list->precision > len)
	{
		i = list->precision - len;
		arr2 = ft_alloc(i + 1);
		ft_memset(arr2, '0', i);
	}
	else
		arr2 = ft_alloc(1);
	if (list->flag == '#' && arr2[1] == '\0')
		i += 1;
	arr1 = fill_1(list, len, i);
	if (list->flag == '#' && arr2[0] == '\0')
	{
		tmp = ft_strjoin("0", arr2);
		print(num, arr1, tmp, list);
	}
	else
		print(num, arr1, arr2, list);
}

static uintmax_t	find_n(t_format *list, va_list *ar)
{
	uintmax_t		i;
	unsigned int	j;

	if ((list->modifier == 'l' && list->mod_count == 2) ||
		(list->modifier == 'l' && list->type == 'O'))
		i = va_arg(*ar, unsigned long long int);
	else if (list->modifier == 'l' || list->type == 'O')
		i = va_arg(*ar, unsigned long int);
	else if (list->modifier == 'j')
		i = va_arg(*ar, uintmax_t);
	else if (list->modifier == 'z')
		i = va_arg(*ar, size_t);
	else
		i = va_arg(*ar, unsigned int);
	j = i;
	if (list->modifier == 'h' && list->mod_count == 2 && list->type != 'O')
		i = (unsigned char)((unsigned int)j);
	if (list->modifier == 'h' && list->mod_count != 2 && list->type != 'O')
		i = (unsigned short int)((unsigned int)j);
	return (i);
}

void				print_o(va_list *ar, t_format *list)
{
	int				len;
	char			*num;
	uintmax_t		i;

	i = find_n(list, ar);
	num = ft_itoa_ubase(i, 8, 0);
	if ((list->precision == 0 && i == 0) || (list->flag == '#' && i == 0))
	{
		free(num);
		num = malloc(1);
		num[0] = '\0';
	}
	len = ft_strlen(num);
	if (list->sign == '-')
		list->nul = 0;
	fill(len, num, list);
}
