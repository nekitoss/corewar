/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:30:39 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/13 18:39:25 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*newstr(int n, char s)
{
	char	*str;

	str = ft_strnew(n);
	while (--n != 0)
		str[n] = s;
	str[n] = s;
	return (str);
}

void		pass_some(char **str)
{
	while (**str && **str != '\0')
	{
		if (**str == '%' && *(*str + 1) != '%')
			break ;
		else if (**str == '%' && *(*str + 1) == '%')
		{
			(*str) += 2;
			continue;
		}
		(*str)++;
	}
}

char		is_convers(char c, char *str)
{
	while (*str != '\0')
	{
		if (c == *str)
			return (c);
		str++;
	}
	return (0);
}

void		pass_this(char **str)
{
	while (is_convers(**str, "sSpdDioOuUxXcC") == 0 && **str != '\0')
		(*str)++;
	if (**str != '\0')
		(*str)++;
}

char		*parse_flags(char *str)
{
	char	*ret_fl;

	ret_fl = newstr(5, ' ');
	while (*str && *str != '\0' && is_convers(*str, "sSpdDioOuUxXcC") == 0)
	{
		if (*str == '-')
			ret_fl[0] = '1';
		if (*str == '+')
			ret_fl[1] = '1';
		if (*str == '0' && !ft_isdigit(*(str - 1)) && *(str - 1) != '.')
			ret_fl[2] = '1';
		if (*str == '#')
			ret_fl[3] = '1';
		if (*str == ' ')
			ret_fl[4] = '1';
		str++;
	}
	return (ret_fl);
}
