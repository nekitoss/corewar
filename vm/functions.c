#include "../corewar.h"

void				f_live(t_core *ls, t_proc *proc, g_my_op *func)
{
	int	alive_num;

	alive_num = func->is_codage;
	alive_num = read_data_block(ls, proc->old_pc + 1, 4);
	shift_pc(&(proc->pc), 5);
	if (ls->args->num_debug & 4) {printf("P%5zu | live %d\n", proc->number, alive_num);}
	if (alive_num < 0 && alive_num >= (ls->num_of_players * -1))
	{
		alive_num = (alive_num * (-1)) - 1;
		(((ls->players)[alive_num])->sum_lives_in_current_period)++;
		((ls->players)[alive_num])->last_live = ls->cycle;
		if (ls->args->num_debug & 1) {printf("Player %d (%s) is said to be alive\n", (alive_num + 1) * -1, ((ls->players)[alive_num])->name);}
	}
	(ls->gen_lives_in_current_period)++;
	proc->is_alive = TRUE;
	proc->alive_at = ls->cycle;

}

void				f_ld(t_core *ls, t_proc *proc, g_my_op *func)
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
		if (ls->args->num_debug & 4) {printf("P%5zu | ld %d r%d\n", proc->number, what, where);}
	}
}

void				f_st(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;
	int tmp;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		tmp = P_PAR[0];
		convert_param_to_data(proc, 0);
		what = P_PAR[0];
		if (ident_param(P_COD_B, 1) & T_REG)
			P_REG[P_PAR[1]] = what;
		else
		{
			where = ((P_PAR[1] % IDX_MOD) + (int)proc->old_pc) % MEM_SIZE;
			write_data_block(proc, what, where, 4);
		}
		if (ls->args->num_debug & 4) {printf("P%5zu | st r%d %d\n", proc->number, tmp, P_PAR[1]);}
	}
}

void				f_add(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		if (ls->args->num_debug & 4) {printf("P%5zu | add r%d r%d r%d\n", proc->number, P_PAR[0], P_PAR[1], P_PAR[2]);}
		convert_param_to_data(proc, 0);
		convert_param_to_data(proc, 1);
		what = P_PAR[0] + P_PAR[1];
		where = P_PAR[2];
		P_REG[where] = what;
		if (!what)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
}

void				f_sub(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		if (ls->args->num_debug & 4) {printf("P%5zu | sub r%d r%d r%d\n", proc->number, P_PAR[0], P_PAR[1], P_PAR[2]);}
		convert_param_to_data(proc, 0);
		convert_param_to_data(proc, 1);
		what = P_PAR[0] - P_PAR[1];
		where = P_PAR[2];
		P_REG[where] = what;
		if (!what)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
}

void				f_and(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data(proc, 0);
		convert_param_to_data(proc, 1);
		what = P_PAR[0] & P_PAR[1];
		where = P_PAR[2];
		P_REG[where] = what;
		if (!what)
			proc->carry = 1;
		else
			proc->carry = 0;
		if (ls->args->num_debug & 4) {printf("P%5zu | and %d %d r%d\n", proc->number, P_PAR[0], P_PAR[1], P_PAR[2]);}
	}
}

void				f_or(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data(proc, 0);
		convert_param_to_data(proc, 1);
		what = P_PAR[0] | P_PAR[1];
		where = P_PAR[2];
		P_REG[where] = what;
		if (!what)
			proc->carry = 1;
		else
			proc->carry = 0;
		if (ls->args->num_debug & 4) {printf("P%5zu | or %d %d r%d\n", proc->number, P_PAR[0], P_PAR[1], P_PAR[2]);}
	}
}

void				f_xor(t_core *ls, t_proc *proc, g_my_op *func)
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
		if (ls->args->num_debug & 4) {printf("P%5zu | xor %d %d r%d\n", proc->number, P_PAR[0], P_PAR[1], P_PAR[2]);}
	}
}

void				f_zjmp(t_core *ls, t_proc *proc, g_my_op *func)
{
	int where;

	where = func->is_codage;
	if (proc->carry)
		where = read_data_block(ls, proc->old_pc + 1, 2) % IDX_MOD;
	else
		where = 3;
	if (ls->args->num_debug & 4) {printf("P%5zu | zjmp %d %s\n", proc->number, read_data_block(ls, proc->old_pc + 1, 2), ((proc->carry) ? "OK" : "FAILED"));}
	shift_pc(&(proc->pc), where);
}

void				f_ldi(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data(proc, 0);
		convert_param_to_data(proc, 1);
		what = read_data_block(ls ,((int)proc->old_pc + ((P_PAR[0] + P_PAR[1]) % IDX_MOD)), 4);
		where = P_PAR[2];
		P_REG[where] = what;
		if (ls->args->num_debug & 4) {printf("P%5zu | ldi %d %d r%d\n", proc->number, P_PAR[0], P_PAR[1], P_PAR[2]);
						printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", P_PAR[0], P_PAR[1], P_PAR[0] + P_PAR[1], ((int)proc->old_pc + ((P_PAR[0] + P_PAR[1]) % IDX_MOD)));}
	}
}

void				f_sti(t_core *ls, t_proc *proc, g_my_op *func)
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
		where = (((P_PAR[1] + P_PAR[2]) % IDX_MOD) + (int)proc->old_pc) % MEM_SIZE;
		write_data_block(proc, what, where, 4);
		if (ls->args->num_debug & 4) {printf("P%5zu | sti r%d %d %d\n", proc->number, P_PAR[0], P_PAR[1], P_PAR[2]);
						printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", P_PAR[1], P_PAR[2], P_PAR[1] + P_PAR[2], ((int)proc->old_pc + ((P_PAR[1] + P_PAR[2]) % IDX_MOD)));}
	}
}

void				f_fork(t_core *ls, t_proc *proc, g_my_op *func)
{
	int where;

	where = func->is_codage;
	shift_pc(&(proc->pc), 3);
	where = read_data_block(ls, proc->old_pc + 1, 2);
	if (ls->args->num_debug & 4) {printf("P%5zu | fork %d ", proc->number, where);}
	where = (int)proc->old_pc + (where % IDX_MOD);
	if (ls->args->num_debug & 4) {printf("(%d)\n", where);}
	add_proc_on_top(ls, where, proc->belong_to_player);
	clone_proc(proc, ls->processes_list);
}

void				f_lld(t_core *ls, t_proc *proc, g_my_op *func)
{//no idxmod от слова вообще
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
		if (ls->args->num_debug & 4) {printf("P%5zu | lld %d r%d\n", proc->number, what, where);}
	}
}

void				f_lldi(t_core *ls, t_proc *proc, g_my_op *func)
{//no idxmod к сумме
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->old_pc + 1, 1);
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data(proc, 0);
		convert_param_to_data(proc, 1);
		what = read_data_block(ls ,(int)proc->old_pc + (P_PAR[0] + P_PAR[1]), 4);
		where = P_PAR[2];
		P_REG[where] = what;
		if (ls->args->num_debug & 4) {printf("P%5zu | lldi %d %d r%d\n", proc->number, P_PAR[0], P_PAR[1], P_PAR[2]);
						printf("       |  -> load from %d + %d = %d (with pc %d)\n", P_PAR[0], P_PAR[1], P_PAR[0] + P_PAR[1], (int)proc->old_pc + (P_PAR[0] + P_PAR[1]));}
	}
}

void				f_lfork(t_core *ls, t_proc *proc, g_my_op *func)
{//no idxmod вообще
	int where;

	where = func->is_codage;
	shift_pc(&(proc->pc), 3);
	where = read_data_block(ls, proc->old_pc + 1, 2);
	if (ls->args->num_debug & 4) {printf("P%5zu | lfork %d (%d)\n", proc->number, where, where);}
	where = (int)proc->old_pc + where;
	add_proc_on_top(ls, where, proc->belong_to_player);
	clone_proc(proc, ls->processes_list);
}

void				f_aff(t_core *ls, t_proc *proc, g_my_op *func)
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
