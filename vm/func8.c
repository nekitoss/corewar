/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:41:21 by nekitoss          #+#    #+#             */
/*   Updated: 2017/10/27 21:41:22 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void				set_initial_code_color(char *colors, int pl_num, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		*colors = pl_num;
		colors++;
		i++;
	}
}

int					cmp_one_param(t_my_op *func, unsigned char coding_byte,
																int param_num)
{
	if (ident_param(coding_byte, param_num) & func->type_of_params[param_num])
		return (1);
	return (0);
}

void				add_proc_on_top(t_core *ls, unsigned int pc,
											int belong_to_player)
{
	t_proc	*new;

	new = ft_memalloc(sizeof(t_proc));
	new->reg[1] = belong_to_player;
	new->next = ls->processes_list;
	new->pc = pc % MEM_SIZE;
	new->belong_to_player = belong_to_player;
	new->ls = ls;
	new->execute_at = ls->cycle;
	(ls->pr_cnt)++;
	new->number = ls->pr_cnt;
	ls->processes_list = new;
}
