/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nekit_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:48:33 by nekitoss          #+#    #+#             */
/*   Updated: 2017/10/27 21:48:36 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_my_op				g_tab[17] =
{
	{0, 0, {0, 0, 0}, 0, 0, 0, ""},
	{f_live, 1, {T_DIR, 0, 0}, 1, 10, 4, "live"},
	{f_ld, 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, 4, "ld"},
	{f_st, 2, {T_REG, T_IND | T_REG, 0}, 3, 5, 0, "st"},
	{f_add, 3, {T_REG, T_REG, T_REG}, 4, 10, 0, "add"},
	{f_sub, 3, {T_REG, T_REG, T_REG}, 5, 10, 0, "sub"},
	{f_and, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 4, "and"},
	{f_or, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 4, "or"},
	{f_xor, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 4, "xor"},
	{f_zjmp, 1, {T_DIR, 0, 0}, 9, 20, 2, "zjmp"},
	{f_ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 2, "ldi"},
	{f_sti, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 2, "sti"},
	{f_fork, 1, {T_DIR, 0, 0}, 12, 800, 2, "fork"},
	{f_lld, 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, 4, "lld"},
	{f_lldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 2,
		"lldi"},
	{f_lfork, 1, {T_DIR, 0, 0}, 15, 1000, 2, "lfork"},
	{f_aff, 1, {T_REG, 0, 0}, 16, 2, 0, "aff"}
};

void				init_my_player_and_process(t_core *ls)
{
	int i;

	i = 0;
	ls->num_of_players = ls->args->cnt_player;
	ls->cycle_to_die = CYCLE_TO_DIE;
	ls->next_cycle_to_die = ls->cycle_to_die;
	while (i < ls->num_of_players)
	{
		add_proc_on_top(ls, (i * (MEM_SIZE / ls->num_of_players)),
			((ls->players)[i])->num);
		ft_memcpy(&(ls->field)[(i * (MEM_SIZE / ls->num_of_players))],
			((ls->players)[i])->program_code, ((ls->players)[i])->size_code);
		set_initial_code_color(&(ls->colors)[(i * (MEM_SIZE /
				ls->num_of_players))], ((ls->players)[i])->num,
				((ls->players)[i])->size_code);
		PROC_LIST->opcode_to_execute = *(((ls->players)[i])->program_code);
		if (PROC_LIST->opcode_to_execute < 17
					&& PROC_LIST->opcode_to_execute > 0)
			PROC_LIST->execute_at = ls->cycle
			+ (g_tab[(PROC_LIST->opcode_to_execute)]).cycles_to_exec;
		i++;
	}
	ls->num_of_processes = ls->num_of_players;
}

void				opcode(t_core *ls, t_proc *proc)
{
	if (proc->opcode_to_execute < 17 && proc->opcode_to_execute > 0)
	{
		proc->old_pc = proc->pc;
		((g_tab[(proc->opcode_to_execute)]).func)(ls,
						proc, &(g_tab[(proc->opcode_to_execute)]));
	}
	else
	{
		shift_pc(&(proc->pc), 1);
	}
	proc->opcode_to_execute = read_data_block(ls, proc->pc, 1);
	if (proc->opcode_to_execute < 17 && proc->opcode_to_execute > 0)
		proc->execute_at = ls->cycle
					+ (g_tab[proc->opcode_to_execute]).cycles_to_exec;
	else
		proc->execute_at = ls->cycle + 1;
}

void				clone_proc(t_proc *father, t_proc *son)
{
	if (father && son)
	{
		ft_memcpy(son->reg, father->reg,
			(REG_NUMBER + 1) * sizeof(*(father->reg)));
		son->is_alive = father->is_alive;
		son->carry = father->carry;
		son->opcode_to_execute = read_data_block(father->ls, son->pc, 1);
		if (son->opcode_to_execute < 17 && son->opcode_to_execute > 0)
			son->execute_at = father->ls->cycle
				+ (g_tab[son->opcode_to_execute]).cycles_to_exec;
		else
			son->execute_at = father->ls->cycle + 1;
		son->belong_to_player = father->belong_to_player;
	}
}

int					main(int argc, char **argv)
{
	t_core	*ls;
	t_proc	*current_process;

	ls = ft_memalloc(sizeof(t_core));
	preparate(ls, argc, argv);
	if (ls->args->fl_visual == 1)
		start_draw(ls);
	while (1)
	{
		if (ls->args->num_debug & 2 && ls->cycle)
			debug_2_1(ls->cycle);
		armageddon(ls);
		current_process = ls->processes_list;
		while (current_process)
		{
			if (current_process->execute_at == ls->cycle)
				opcode(ls, current_process);
			current_process = current_process->next;
		}
		if (ls->args->fl_visual == 1)
			drawing(ls);
		(ls->cycle)++;
	}
	return (0);
}
