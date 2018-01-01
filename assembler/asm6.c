/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/19 18:46:15 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_parameter(char **s)
{
	if (**s == '%')
		check_dir(s);
	else if (**s == 'r')
		check_reg(s);
	else if (**s == ':')
		check_indir(s);
	else if (ft_isdigit(**s) || **s == '-')
		check_num(s);
	else
		error("Parameter error");
}

void		check_args(char *s, int index)
{
	int		i;

	i = 0;
	pass_spaces(&s);
	while (ft_isalpha(*s))
		s++;
	if (*s != ' ' && *s != '%' && *s != '\t')
		error("Parameter error");
	s++;
	pass_spaces(&s);
	while (i < g_tab[index].arg_count)
	{
		check_parameter(&s);
		while (*s == ' ' || *s == '\t' || *s == ',')
			s++;
		i++;
	}
}

t_commands	*get_empty_struc(t_commands *c)
{
	while (c->next)
		c = c->next;
	if (ft_strequ(c->command_name, "start"))
		return (c);
	else
	{
		c->next = new_commands();
		c = c->next;
		return (c);
	}
}

int			check_type(char **s, int ind, int index)
{
	int		i;

	i = 0;
	if (**s == 'r')
		i = 1;
	if (**s == '%')
		i = 2;
	if (**s == ':' || ft_isdigit(**s) || **s == '-')
	{
		i = 4;
		if ((ind == 1 && (index == 9 || index == 13)) ||
				(ind == 2 && index == 10))
			error("Incorect parameter type");
	}
	if ((i & g_tab[index].arg[ind]) == 0)
		error("Incorect parameter type");
	return (i);
}

void		goto_next_param(char **s)
{
	pass_spaces(s);
	if (**s == ',')
	{
		(*s)++;
		pass_spaces(s);
	}
}
