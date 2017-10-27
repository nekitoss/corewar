/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/19 18:58:24 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*get_lb_name(char *s)
{
	char		*str;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	while (ft_strchr(LABEL_CHARS, s[i]))
		i++;
	str = (char*)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int				check_repeat(t_label *lb, char *s)
{
	if (!(lb->name))
		return (0);
	while (lb)
	{
		if (ft_strequ(s, lb->name))
			return (1);
		lb = lb->next;
	}
	return (0);
}

int				add_label(t_asm *masm, char *s)
{
	t_label		*lb;
	char		*lb_name;

	lb = masm->labels;
	lb_name = get_lb_name(s);
	if (check_repeat(lb, lb_name))
		return (-1);
	if (lb->byte_num != -1)
	{
		while (lb->next)
			lb = lb->next;
		lb->next = new_labels();
		lb = lb->next;
	}
	lb->name = lb_name;
	lb->byte_num = masm->count_byte;
	return ((int)ft_strlen(lb->name));
}

void			pass_spaces(char **s)
{
	while (**s == '\t' || **s == ' ')
		(*s)++;
}

void			check_separator(char *s, int index)
{
	int			count;

	count = 0;
	while (*s != '\n')
	{
		if (*s == SEPARATOR_CHAR && *(s + 1) == SEPARATOR_CHAR)
			error("Separator error \",,\"");
		if (*s == SEPARATOR_CHAR)
			count++;
		s++;
	}
	if (g_tab[index].arg_count != (count + 1))
		error("Separator error");
}
