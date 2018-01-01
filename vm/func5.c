/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:41:02 by nekitoss          #+#    #+#             */
/*   Updated: 2017/10/27 21:41:03 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void				convert_param_to_data(t_proc *proc, int par_num)
{
	int coding_byte;

	coding_byte = ident_param(P_COD_B, par_num);
	if (coding_byte & T_REG)
		P_PAR[par_num] = (int)(P_REG[(P_PAR[par_num])]);
	else if (coding_byte & T_IND)
	{
		P_PAR[par_num] = ((P_PAR[par_num] % IDX_MOD)
							+ (int)proc->old_pc) % MEM_SIZE;
		P_PAR[par_num] = (int)read_data_block(proc->ls, P_PAR[par_num], 4);
	}
}

void				convert_param_to_data_no_idx(t_proc *proc, int par_num)
{
	int coding_byte;

	coding_byte = ident_param(P_COD_B, par_num);
	if (coding_byte & T_REG)
		P_PAR[par_num] = (int)(P_REG[(P_PAR[par_num])]);
	else if (coding_byte & T_IND)
	{
		P_PAR[par_num] = (P_PAR[par_num] + (int)proc->old_pc) % MEM_SIZE;
		P_PAR[par_num] = (int)read_data_block(proc->ls, P_PAR[par_num], 4);
	}
}

unsigned char		ident_param(unsigned char coding_byte, int param_num)
{
	coding_byte = (coding_byte & (0b11 << ((3 - param_num) * 2)))
								>> ((3 - param_num) * 2);
	if (coding_byte == 3)
		coding_byte = 4;
	return (coding_byte);
}

int					calculate_pc_shift(t_my_op *func, unsigned char coding_byte,
																	int par_num)
{
	coding_byte = ident_param(coding_byte, par_num);
	if (coding_byte & T_REG)
		return (1);
	else if (coding_byte & T_IND)
		return (2);
	else if (coding_byte & T_DIR)
	{
		if (func->bytes_for_tdir == 2)
			return (2);
		else
			return (4);
	}
	else
		return (0);
}

int					read_non_conv_parameters_and_shift(t_my_op *func,
															t_proc *proc)
{
	int			i;
	int			correct_params;

	correct_params = 1;
	i = 0;
	while (i < func->num_of_params)
	{
		P_PAR[i] = (int)read_data_block(proc->ls, proc->pc,
							calculate_pc_shift(func, P_COD_B, i));
		if (cmp_one_param(func, P_COD_B, i))
		{
			if ((ident_param(P_COD_B, i) & T_REG)
							&& (P_PAR[i] < 1 || P_PAR[i] > 16))
				correct_params = 0;
			if ((ident_param(P_COD_B, i) & T_DIR) && func->bytes_for_tdir == 2)
				P_PAR[i] = (int)((short)P_PAR[i]);
		}
		else
			correct_params = 0;
		shift_pc(&(proc->pc), calculate_pc_shift(func, P_COD_B, i));
		i++;
	}
	return (correct_params);
}
