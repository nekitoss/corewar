/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 16:18:00 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/14 16:17:56 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip_ws_symb(const char *str)
{
	char	*new_str;

	new_str = (char *)((size_t)str);
	while (ft_isspace(*new_str))
		new_str++;
	return (new_str);
}

int			ft_atoi(const char *str)
{
	char	sign;
	int		result;
	char	*str_no_ws;

	sign = 1;
	result = 0;
	if (!*str)
		return (0);
	str_no_ws = skip_ws_symb(str);
	if (*str_no_ws == '+')
		str_no_ws++;
	else if (*str_no_ws == '-')
	{
		str_no_ws++;
		sign = -1;
	}
	while (*str_no_ws && ft_isdigit(*str_no_ws))
		result = result * 10 + (*(str_no_ws++)) - '0';
	return (sign * result);
}
