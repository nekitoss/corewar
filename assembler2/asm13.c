/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm13.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 18:36:49 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/23 18:45:08 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_stcmp1(char *s1, char *s2)
{
	int		i;
	char	*s;

	s = s1;
	i = 0;
	while (*s1 == *s2 && (*s1 != '\0' || *s2 != '\0'))
	{
		i++;
		s1++;
		s2++;
	}
	if (*s1 != '\0')
		return (0);
	if (*s2 != ' ' && *s2 != '\t' && *s2 != '%')
		return (-1);
	if (*s2 == '%')
		if (ft_strequ(s, "st") || ft_strequ(s, "add")
			|| ft_strequ(s, "sub") || ft_strequ(s, "sti")
			|| ft_strequ(s, "aff"))
			return (-1);
	return (i);
}

int			is_command1(char *s)
{
	int		i;
	int		a;
	char	*st;

	i = 15;
	while (*s == ' ' || *s == '\t')
		s++;
	while (i >= 0)
	{
		st = (g_tab[i]).name;
		a = ft_stcmp1(st, s);
		if (a > 0 && a == (int)ft_strlen(st))
			return (i);
		i--;
	}
	return (-1);
}

int			label_or_comm(char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (is_label(s))
		return (1);
	if (is_command1(s) != -1)
		return (2);
	return (0);
}
