/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/19 18:45:55 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		del_com(char **s)
{
	int		i;

	i = 0;
	while ((*s)[i] != '\0')
	{
		while ((*s)[i] != COMMENT_CHAR && (*s)[i] != ';' && (*s)[i] != '\0')
			i++;
		while ((*s)[i] != '\n' && (*s)[i] != '\0')
			(*s)[i++] = ' ';
	}
}

int			ft_stcmp(char *s1, char *s2)
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
		error("Invalid instruction");
	if (*s2 == '%')
		if (ft_strequ(s, "st") || ft_strequ(s, "add") || ft_strequ(s, "sub")
				|| ft_strequ(s, "sti") || ft_strequ(s, "aff"))
			error("Invalid instruction");
	return (i);
}

int			is_command(char *s)
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
		a = ft_stcmp(st, s);
		if (a > 0 && a == (int)ft_strlen(st))
			return (i);
		i--;
	}
	return (-1);
}

int			is_label(char *s)
{
	while (*s != '\n')
	{
		if (!ft_strchr(LABEL_CHARS, *s))
			break ;
		s++;
	}
	if (*s == LABEL_CHAR)
		return (1);
	return (0);
}

int			check_label_or_comm(char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (!ft_strchr(LABEL_CHARS, *s))
		error("Lexical error in row");
	if (is_label(s))
		return (0);
	if (is_command(s) != -1)
		return (1);
	error("Lexical error");
	return (0);
}
