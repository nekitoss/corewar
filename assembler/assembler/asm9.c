/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm9.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/16 14:15:18 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	valid_code(t_asm *masm, char *str, header_t *head)
{
	valid_head(head, &str);
	del_com(&str);
	while (*str != '\0' && !is_empty(str))
	{
		if (!pass_it(str) && check_label(masm, &str))
			check_command(masm, &str);
		while (*str != '\n')
			str++;
		if (*str == '\n')
			str++;
	}
}

char		*make_name(char *s)
{
	int		i;
	char	*ret;

	i = 0;
	while (s[i] != '.')
		i++;
	ret = (char*)malloc(sizeof(char) * (i + 5));
	i = 0;
	while (s[i] != 's')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i++] = 'c';
	ret[i++] = 'o';
	ret[i] = 'r';
	return (ret);
}

int		get_ind(char *s)
{
	int  i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_tab[i].name, s))
			break ;
		i++;
	}
	return (i);
}

int 	get_codege(char *p, int i)
{
	int	code;

	if (p[i] == 'I')
		code = 3;
	else if (p[i] == 'R')
		code = 1;
	else if (p[i] == 'D' || p[i] == 'd')
		code = 2;
	else
		code = 0;
	return (code);
}

void	write_codage(int fdwrite, t_commands *comm)
{
	int codage;

	codage = 0;
	codage += get_codege(comm->P, 0);
	codage = codage << 2;
	codage += get_codege(comm->P, 1);
	codage = codage << 2;
	codage += get_codege(comm->P, 2);
	codage = codage << 2;
	write(fdwrite, &codage, 1);
}
