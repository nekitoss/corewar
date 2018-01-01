/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/16 18:48:30 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			add_to_struct(t_asm *masm, int ind, char **s)
{
	t_commands	*comm;
	int			i;

	i = 0;
	comm = get_empty_struc(masm->commands);
	comm->command_name = ft_strdup(g_tab[ind].name);
	*s += ft_strlen(comm->command_name);
	pass_spaces(s);
	comm->size = masm->count_byte;
	while (i < g_tab[ind].arg_count)
	{
		masm->count_byte += set_param(comm, i, ind, s);
		while (**s != ',' && **s != ' ' && **s != '\t' && **s != '\n')
			(*s)++;
		goto_next_param(s);
		i++;
	}
	masm->count_byte += 1 + g_tab[ind].codage;
	if (**s != '\n')
		error("ERROR. Incorect symbol after command");
}

void			check_command(t_asm *masm, char **str)
{
	char		*s;
	int			index;

	s = *str;
	if (!check_label_or_comm(s))
		error("Syntax error:  LABEL");
	index = is_command(s);
	if (index != -1)
		check_separator(s, index);
	else
		error("Zdes mozhet bit vasha oshibka");
	check_args(s, index);
	pass_spaces(&s);
	add_to_struct(masm, index, &s);
	while (**str != '\n')
		(*str)++;
}

int				check_label(t_asm *masm, char **str)
{
	char		*s;

	s = *str;
	if (check_label_or_comm(s) == 1)
		return (1);
	add_label(masm, s);
	while (**str != LABEL_CHAR)
		(*str)++;
	(*str)++;
	while (**str == ' ' || **str == '\t')
		(*str)++;
	if (**str == '\n')
		return (0);
	return (1);
}

int				is_empty(char *s)
{
	while ((*s == ' ' || *s == '\t') && *s != '\n')
		s++;
	if (*s == '\0')
		return (1);
	return (0);
}

int				pass_it(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '\n')
		return (1);
	return (0);
}
