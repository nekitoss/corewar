/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:33:19 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/19 17:49:46 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print(char *s, char *arr1, char *arr2, t_format *list)
{
	if (list->sign == '-')
	{
		if (arr1[0] == '0')
		{
			print_str(arr1);
			print_str(s);
			print_str(arr2);
		}
		else
		{
			print_str(s);
			print_str(arr2);
			print_str(arr1);
		}
	}
	else
	{
		print_str(arr2);
		print_str(arr1);
		print_str(s);
	}
	free(arr1);
	free(arr2);
	free(s);
}

intmax_t	typecheck(intmax_t i, t_format *list)
{
	intmax_t	r;

	r = i;
	if ((list->type == 'd' || list->type == 'i') && list->modifier == 'h')
	{
		if (list->mod_count != 2)
			r = (short)r;
		else
			r = (char)r;
	}
	return (r);
}

static void	check(char *s, char *arr2)
{
	char		*t;
	char		*tmp;
	int			i;

	if ((s[0] == '-' || s[0] == ' ' || s[0] == '+') && arr2[0] == '0')
	{
		t = malloc(2);
		t[0] = s[0];
		t[1] = '\0';
		tmp = ft_strjoin(t, arr2);
		free(arr2);
		i = ft_strlen(s) - 1;
		ft_memmove(s, s + 1, i);
		s[i] = '\0';
		arr2 = ft_strdup(tmp);
		free(tmp);
	}
}

static char	*arrs2(t_format *list, char *s)
{
	char		*arr2;

	if (list->width > (int)ft_strlen(s))
	{
		arr2 = ft_alloc(list->width - (int)ft_strlen(s) + 1);
		if (list->nul)
			ft_memset(arr2, '0', list->width - (int)ft_strlen(s));
		else
			ft_memset(arr2, ' ', list->width - (int)ft_strlen(s));
	}
	else
		arr2 = ft_alloc(1);
	return (arr2);
}

void		arrs(t_format *list, char *s)
{
	char		*arr1;
	char		*arr2;

	arr1 = NULL;
	arr2 = NULL;
	if (list->precision > (int)ft_strlen(s))
	{
		arr1 = ft_alloc(list->precision - (int)ft_strlen(s) + 1);
		ft_memset(arr1, '0', list->precision - (int)ft_strlen(s));
		if (list->width > list->precision)
		{
			arr2 = ft_alloc(list->width - list->precision + 1);
			ft_memset(arr2, ' ', list->width - list->precision);
		}
		else
			arr2 = ft_alloc(1);
	}
	else
	{
		arr1 = ft_alloc(1);
		arr2 = arrs2(list, s);
	}
	check(s, arr2);
	print(s, arr1, arr2, list);
}
