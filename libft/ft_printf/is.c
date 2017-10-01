/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:14:29 by rhulam            #+#    #+#             */
/*   Updated: 2017/04/17 13:15:49 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_type(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i' ||
		c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C' || c == 'f' || c == 'F' || c == '%')
		return (1);
	return (0);
}

int		is_flag(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == '+' || c == ' ')
		return (1);
	return (0);
}

int		is_width(char c)
{
	if (c == '*' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int		is_precision(char c)
{
	if (c == '.')
		return (1);
	return (0);
}

int		is_modifier(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == 'L' || c == 'b')
		return (1);
	return (0);
}
