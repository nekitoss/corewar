/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:34:21 by nekitoss          #+#    #+#             */
/*   Updated: 2017/10/27 21:34:22 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void				f_xor(t_core *ls, t_proc *proc, t_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data(proc, 0);
		convert_param_to_data(proc, 1);
		what = P_PAR[0] ^ P_PAR[1];
		where = P_PAR[2];
		P_REG[where] = what;
		if (!what)
			proc->carry = 1;
		else
			proc->carry = 0;
		if (ls->args->num_debug & 4)
			debug_4(proc, func, 4);
	}
}

void				f_zjmp(t_core *ls, t_proc *proc, t_my_op *func)
{
	int where;

	if (proc->carry)
		where = read_data_block(ls, proc->old_pc + 1, 2) % IDX_MOD;
	else
		where = 3;
	P_PAR[0] = read_data_block(ls, proc->old_pc + 1, 2) % IDX_MOD;
	if (ls->args->num_debug & 4)
		debug_4(proc, func, 0);
	shift_pc(&(proc->pc), where);
}

void				f_ldi(t_core *ls, t_proc *proc, t_my_op *func)
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
				((int)proc->old_pc + ((P_PAR[0] + P_PAR[1]) % IDX_MOD)), 4);
		where = P_PAR[2];
		P_REG[where] = what;
		if (ls->args->num_debug & 4)
			debug_4(proc, func, 4);
	}
}

void				f_sti(t_core *ls, t_proc *proc, t_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		what = P_REG[P_PAR[0]];
		convert_param_to_data(proc, 1);
		convert_param_to_data(proc, 2);
		where = (((P_PAR[1] + P_PAR[2]) % IDX_MOD)
					+ (int)proc->old_pc) % MEM_SIZE;
		write_data_block(proc, what, where, 4);
		if (ls->args->num_debug & 4)
			debug_4(proc, func, 1);
	}
}

void				f_fork(t_core *ls, t_proc *proc, t_my_op *func)
{
	int where;

	shift_pc(&(proc->pc), 3);
	where = read_data_block(ls, proc->old_pc + 1, 2);
	P_PAR[0] = where;
	if (ls->args->num_debug & 4)
		debug_4(proc, func, 0);
	where = (int)proc->old_pc + (where % IDX_MOD);
	add_proc_on_top(ls, where, proc->belong_to_player);
	clone_proc(proc, ls->processes_list);
}
