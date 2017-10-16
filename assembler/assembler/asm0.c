/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm0.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/16 14:11:51 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void error(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
	exit(1);
}

t_label		*new_labels()
{
	t_label	*ret;

	ret = (t_label*)malloc(sizeof(t_label));
	ret->name = NULL;
	ret->byte_num = 0;
	ret->next = NULL;
	return (ret);
}

t_commands		*new_commands()
{
	t_commands	*ret;
	int 		i;

	i = 0;
	ret = (t_commands*)malloc(sizeof(t_commands));
	ret->command_name = NULL;
	ret->labels = (char**)malloc(sizeof(char*) * 3);
	ret->P = (char*)malloc(sizeof(char) * 3);
	ret->P[3] = '\0';
	ret->param = (int*)malloc(sizeof(int) * 3);
	ft_bzero(ret->param, 3 * sizeof(int));
	while (i < 3)
	{
		ret->labels[i] = NULL;
		ret->param[i] = 0;
		ret->P[i] = 'O';
		i++;
	}
	ret->codage = 0;
	ret->size = 0;
	ret->next = NULL;
	return (ret);
}

t_asm	*new_struct()
{
	t_asm	*ret;

	ret = (t_asm*)malloc(sizeof(t_asm));
	ret->labels = new_labels();
	ret->commands = new_commands();
	ret->head = NULL;
	ret->count_byte = 0;
	return (ret);
}

t_validation *new_valid()
{
	t_validation *ret;

	ret = (t_validation*)malloc(sizeof(t_validation));
	ft_bzero(ret, sizeof(ret));
	return (ret);
}
