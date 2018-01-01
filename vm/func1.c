/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:34:07 by nekitoss          #+#    #+#             */
/*   Updated: 2017/10/27 21:34:09 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void				debug_1(int p_num, char *name)
{
	ft_putstr("Player ");
	ft_putnbr(p_num);
	ft_putstr(" (");
	ft_putstr(name);
	ft_putendl(") is said to be alive");
}

void				put_spaces(size_t num)
{
	if (num < 10)
		ft_putstr("    ");
	else if (num < 100)
		ft_putstr("   ");
	else if (num < 1000)
		ft_putstr("  ");
	else if (num < 10000)
		ft_putstr(" ");
}

void				debug_4(t_proc *proc, t_my_op *func, int r)
{
	ft_putchar('P');
	put_spaces(proc->number);
	ft_putnbr_u(proc->number);
	ft_putstr(" | ");
	ft_putstr(func->name);
	ft_putchar(' ');
	(r & 1) ? ft_putchar('r') : 0;
	ft_putnbr(P_PAR[0]);
	if (func->function_num == 9)
		ft_putstr((proc->carry) ? " OK" : " FAILED");
	if (func->num_of_params > 1)
	{
		ft_putchar(' ');
		(r & 2) ? ft_putchar('r') : 0;
		ft_putnbr(P_PAR[1]);
	}
	if (func->num_of_params > 2)
	{
		ft_putchar(' ');
		(r & 4) ? ft_putchar('r') : 0;
		ft_putnbr(P_PAR[2]);
	}
	ft_putendl("");
}

void				f_live(t_core *ls, t_proc *proc, t_my_op *func)
{
	int	alive_num;

	alive_num = read_data_block(ls, proc->old_pc + 1, 4);
	P_PAR[0] = alive_num;
	shift_pc(&(proc->pc), 5);
	if (ls->args->num_debug & 4)
		debug_4(proc, func, 0);
	if (alive_num < 0 && alive_num >= (ls->num_of_players * -1))
	{
		alive_num = (alive_num * (-1)) - 1;
		(((ls->players)[alive_num])->sum_lives_in_current_period)++;
		((ls->players)[alive_num])->last_live = ls->cycle;
		if (ls->args->num_debug & 1)
			debug_1((alive_num + 1) * -1, ((ls->players)[alive_num])->name);
	}
	(ls->gen_lives_in_current_period)++;
	proc->is_alive = TRUE;
	proc->alive_at = ls->cycle;
}

void				f_ld(t_core *ls, t_proc *proc, t_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data(proc, 0);
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
