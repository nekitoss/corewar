/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:34:26 by nekitoss          #+#    #+#             */
/*   Updated: 2017/10/27 21:40:56 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void				f_lld(t_core *ls, t_proc *proc, t_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data_no_idx(proc, 0);
		if (ls->args->fl_original && ident_param(P_COD_B, 0) & T_IND)
			what = ((int)((short)(((P_PAR[0]) >> 16) & 0xffff)));
		else
			what = P_PAR[0];
		where = P_PAR[1];
		P_REG[where] = what;
		if (!what)
			proc->carry = 1;
		else
			proc->carry = 0;
		if (ls->args->num_debug & 4)
			debug_4(proc, func, 2);
	}
}

void				f_lldi(t_core *ls, t_proc *proc, t_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data(proc, 0);
		convert_param_to_data(proc, 1);
		what = read_data_block(ls,
				(int)proc->old_pc + (P_PAR[0] + P_PAR[1]), 4);
		where = P_PAR[2];
		P_REG[where] = what;
		if (ls->args->num_debug & 4)
			debug_4(proc, func, 4);
	}
}

void				f_lfork(t_core *ls, t_proc *proc, t_my_op *func)
{
	int where;

	shift_pc(&(proc->pc), 3);
	where = read_data_block(ls, proc->old_pc + 1, 2);
	if (ls->args->num_debug & 4)
		debug_4(proc, func, 0);
	where = (int)proc->old_pc + where;
	add_proc_on_top(ls, where, proc->belong_to_player);
	clone_proc(proc, ls->processes_list);
}

void				f_aff(t_core *ls, t_proc *proc, t_my_op *func)
{
	int what;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		what = P_REG[P_PAR[0]] % 256;
		if (ls->args->fl_visual == 0)
		{
			ft_putstr("Aff:");
			ft_putchar(what);
			ft_putendl("");
		}
	}
}
