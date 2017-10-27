/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/18 15:49:39 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				check_quotes(char *str, int i)
{
	int				count;

	count = 0;
	if (i == 1)
		str = ft_strstr(str, ".name");
	else
		str = ft_strstr(str, ".comment");
	while (*str != '\0')
	{
		if (*str == '\"')
			count++;
		str++;
	}
	if (count != 2 && count != 4)
		error("Syntax error. -> \" <- ");
}

char				*check_name(char *str)
{
	t_validation	*v;
	char			*ptr;
	char			*prev;

	v = new_valid();
	prev = ft_strstr(str, ".name");
	ptr = prev;
	while (prev != 0)
	{
		ptr = prev;
		v->count_name++;
		skip_it(&prev);
		prev = ft_strstr(prev, ".name");
	}
	if (v->count_name != 1)
		error("Syntax error. \".name\"");
	check_quotes(str, 1);
	free(v);
	return (get_name(ptr));
}

void				cpy(char **dest, char *str)
{
	int				i;
	int				len;

	i = 0;
	len = (int)ft_strlen(str);
	while (i < len)
	{
		(*dest)[i] = str[i];
		i++;
	}
	free(str);
}

char				*check_comment(char *str)
{
	t_validation	*v;
	char			*ptr;
	char			*prev;

	v = new_valid();
	prev = ft_strstr(str, ".comment");
	ptr = prev;
	while (prev != 0)
	{
		ptr = prev;
		v->count_comment++;
		skip_it(&prev);
		prev = ft_strstr(prev, ".comment");
	}
	if (v->count_comment != 1)
		error("Syntax error. \".comment\"");
	check_quotes(str, 0);
	free(v);
	return (get_name(ptr));
}

void				valid_head(t_header *head, char **str)
{
	char			*t;
	int				i;

	del_only_comments(*str, NULL, NULL);
	t = head->prog_name;
	cpy(&t, check_name(*str));
	if (ft_strlen(t) > 128)
		error("Too large name");
	t = head->comment;
	cpy(&t, check_comment(*str));
	if (ft_strlen(t) > 2048)
		error("Too large comment");
	i = 0;
	while (i < 4)
	{
		if (**str == '\"')
			i++;
		(*str)++;
	}
	(*str)++;
	while (**str == ' ' || **str == '\n' || **str == '\t')
		(*str)++;
	if (**str == '\0')
		error("ERROR. No comands!");
}
