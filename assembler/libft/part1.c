/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:29:15 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/24 18:18:22 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print				*new_struc(void)
{
	t_print			*ret_struc;

	ret_struc = (t_print*)malloc(sizeof(t_print));
	ret_struc->flags = newstr(5, ' ');
	ret_struc->size = 0;
	ret_struc->width = 0;
	ret_struc->precision = 0;
	ret_struc->convers = 0;
	ret_struc->prec_fl = 0;
	return (ret_struc);
}

t_print_list		*new_struc_list(void)
{
	t_print_list	*ret_struc_list;

	ret_struc_list = (t_print_list*)malloc(sizeof(t_print_list));
	ret_struc_list->lst = new_struc();
	ret_struc_list->next = 0;
	return (ret_struc_list);
}

char				*up_or(int up)
{
	char			*hex;

	if (up == 1)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	return (hex);
}

char				*ft_itoa_base(uintmax_t value, int base, int up)
{
	int				i;
	uintmax_t		n;
	char			*s;
	char			*hex;

	hex = up_or(up);
	i = 1;
	n = value;
	while (n /= base)
		i++;
	if ((s = (char*)malloc(sizeof(char) * i + 1)) == 0)
		return (NULL);
	s[i] = 0;
	if (value == 0)
		s[0] = '0';
	n = value;
	while (n)
	{
		s[--i] = hex[n % base];
		n /= base;
	}
	return (s);
}

int					print_some(char **str)
{
	int		how;

	how = 0;
	while (**str && **str != '\0')
	{
		if (**str == '%' && *(*str + 1) != '%')
			break ;
		else if (**str == '%' && *(*str + 1) == '%')
		{
			write(1, "%", 1);
			how++;
			(*str) += 2;
			continue;
		}
		write(1, *str, 1);
		how++;
		(*str)++;
	}
	return (how);
}
