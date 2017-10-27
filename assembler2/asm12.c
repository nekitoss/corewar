/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm12.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 18:35:31 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/23 18:46:08 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					no_quote(char *s)
{
	while (*s != '\n' && *s != '\0')
	{
		if (*s == '\"')
			return (0);
		s++;
	}
	return (1);
}

void				skip_it(char **s)
{
	if (no_quote(*s))
		error("Syntax error \" ENDLINE");
	while (**s != '\"' && **s != '\0')
		(*s)++;
	(*s)++;
	while (**s != '\"' && **s != '\0')
		(*s)++;
	if (**s == '\"')
		(*s)++;
	if (**s == '\0')
		error("Syntax error \" END (null)");
}

char				*check_name_alfa(char *str)
{
	t_validation	*v;
	char			*prev;
	char			*ptr;

	v = new_valid();
	prev = ft_strstr(str, ".name");
	ptr = prev;
	while (prev != 0)
	{
		v->count_name++;
		skip_it(&prev);
		prev = ft_strstr(prev, ".name");
	}
	if (v->count_name != 1)
		error("Syntax error. \".name\"");
	free(v);
	return (ptr);
}

char				*check_comment_alfa(char *str)
{
	t_validation	*v;
	char			*prev;
	char			*ptr;

	v = new_valid();
	prev = ft_strstr(str, ".comment");
	ptr = prev;
	while (prev != 0)
	{
		v->count_comment++;
		skip_it(&prev);
		prev = ft_strstr(prev, ".comment");
	}
	if (v->count_comment != 1)
		error("Syntax error. \".comment\"");
	free(v);
	return (ptr);
}

void				del_only_comments(char *s, char *name, char *comment)
{
	name = check_name_alfa(s);
	comment = check_comment_alfa(s);
	if (!name || !comment)
		error("ERROR (no name or no comment)");
	while (*s != '\0')
	{
		if (*s == '.' && *(s + 1) == '.')
			error("ERROR \"..\"");
		if (s == name || s == comment)
			skip_it(&s);
		else if (*s == COMMENT_CHAR || *s == ';')
			while (*s != '\n')
				*s++ = ' ';
		else if (label_or_comm(s))
			break ;
		else if (*s != ' ' && *s != '\t' && *s != '\n')
			error("ERROR. This is not name or comment");
		s++;
	}
}
