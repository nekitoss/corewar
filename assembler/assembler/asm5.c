/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/17 19:16:58 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_lb_char(char **s)
{
	if (!ft_strchr(LABEL_CHARS, **s))
		error("Parameter error");
	while (**s != ' ' && **s != '\t' && **s != ',' && **s != '\n')
	{
		if (!ft_strchr(LABEL_CHARS, **s))
			error("Parameter error");
		(*s)++;
	}
}

void		check_dir(char **s)
{
	(*s)++;
	if (ft_isdigit(**s) || **s == '-')
	{
		if (**s == '-' && !ft_isdigit(*(*s + 1)))
			error("Parameter error");
		(*s)++;
		if (**s == ' ' || **s == '\t' || **s == ',' || **s == '\n')
			return ;
		if (!ft_isdigit(**s))
			error("Parameter error");
		while (**s != ' ' && **s != '\t' && **s != ',' && **s != '\n')
		{
			if (!ft_isdigit(**s))
				error("Parameter error");
			(*s)++;
		}
	}
	else if (**s == ':')
	{
		(*s)++;
		check_lb_char(s);
	}
	else
		error("Parameter error");
}

void		check_reg(char **s)
{
	char	*str;

	(*s)++;
	if (!ft_isdigit(**s))
		error("Parameter error");
	str = *s;
	while (**s != ' ' && **s != '\t' && **s != ',' && **s != '\n')
	{
		if (!ft_isdigit(**s))
			error("Parameter error");
		(*s)++;
	}
	if (fft_atoi(str) > 99)
		error("Incorect register number");
}

void		check_indir(char **s)
{
	(*s)++;
	if (**s == '-')
		error("Parameter error");
	if (ft_strchr(LABEL_CHARS, **s))
		check_lb_char(s);
	else
		error("Parameter error");
}

void		check_num(char **s)
{
	if (**s == '-' && !ft_isdigit(*(*s + 1)))
		error("Parameter error");
	(*s)++;
	if (**s == ' ' || **s == '\t' || **s == ',' || **s == '\n')
		return ;
	if (!ft_isdigit(**s))
		error("Parameter error");
	while (**s != ' ' && **s != '\t' && **s != ',' && **s != '\n')
	{
		if (!ft_isdigit(**s))
			error("Parameter error");
		(*s)++;
	}
}
