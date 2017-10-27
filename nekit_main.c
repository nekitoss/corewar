#define VIZU 1

#include "corewar.h"

g_my_op				g_tab[17] =
{
	{0, 0, {0, 0, 0}, 0, 0, 0, 0},
	{f_live, 1, {T_DIR, 0, 0}, 1, 10, 0, 4},
	{f_ld, 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, 1, 4},
	{f_st, 2, {T_REG, T_IND | T_REG, 0}, 3, 5, 1, 0},
	{f_add, 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0},
	{f_sub, 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0},
	{f_and, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, 4},
	{f_or, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, 4},
	{f_xor, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, 4},
	{f_zjmp, 1, {T_DIR, 0, 0}, 9, 20, 0, 2},
	{f_ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 2},
	{f_sti, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 2},
	{f_fork, 1, {T_DIR, 0, 0}, 12, 800, 0, 2},
	{f_lld, 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, 1, 4},
	{f_lldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 2},
	{f_lfork, 1, {T_DIR, 0, 0}, 15, 1000, 0, 2},
	{f_aff, 1, {T_REG, 0, 0}, 16, 2, 1, 0}
};

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

int					calculate_pc_shift(g_my_op *func, unsigned char coding_byte,
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

int					read_non_conv_parameters_and_shift(g_my_op *func,
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

short				revert_16_bits_size_t(short num)
{
	num = (num >> 8) | (num << 8);
	return (num);
}

int					revert_32_bits_size_t(int num)
{
	num = ((num >> 24) & 0xff) |
			((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) |
			((num << 24) & 0xff000000);
	return (num);
}

void				write_data_block(t_proc *proc, int data, unsigned int start,
																		int len)
{
	int i;

	i = 0;
	if (len == 4)
		data = revert_32_bits_size_t(data);
	else if (len == 2)
		data = revert_16_bits_size_t(data);
	while (i < len && i < 5)
	{
		proc->ls->field[((start + i) % MEM_SIZE)] = (data & 0xff);
		proc->ls->colors[((start + i) % MEM_SIZE)] = proc->belong_to_player;
		data = data >> OCTET;
		i++;
	}
}

char				read_1_byte(t_core *ls, unsigned int start)
{
	char res;

	res = ls->field[(start % MEM_SIZE)];
	return (res);
}

short				read_2_byte(t_core *ls, unsigned int start)
{
	short res;

	res = ls->field[(start % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 1) % MEM_SIZE)];
	return (res);
}

int					read_4_byte(t_core *ls, unsigned int start)
{
	int	res;

	res = ls->field[(start % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 1) % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 2) % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 3) % MEM_SIZE)];
	return (res);
}

int					read_data_block(t_core *ls, unsigned int start, int len)
{
	int res;

	res = 0;
	if (len == 1)
		res = (int)read_1_byte(ls, start);
	else if (len == 2)
		res = (int)read_2_byte(ls, start);
	else if (len == 4)
		res = read_4_byte(ls, start);
	else if (len == 0)
		res = 0;
	return (res);
}

void				print_data(unsigned char *str, size_t len, size_t width)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (i != 0 && i % width == 0)
			printf("\n");
		printf(" %02x", str[i]);
		i++;
	}
	printf("\n");
}

void				shift_pc(size_t *pc, unsigned int value)
{
	(*pc) = (*pc) + value;
	(*pc) = (*pc) % MEM_SIZE;
}

void				set_next_ex(size_t *next_execution_at, int value)
{
	(*next_execution_at) = (*next_execution_at) + value;
}

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

int					cmp_one_param(g_my_op *func, unsigned char coding_byte,
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

void				game_end(t_core *ls)
{
	int		i;
	ssize_t	last_live_of_winner;
	int		winner_num;

	winner_num = -1;
	last_live_of_winner = -1;
	i = 0;
	while (i < ls->num_of_players)
	{
		if ((ssize_t)(((ls->players)[i])->last_live) > last_live_of_winner)
		{
			last_live_of_winner = ((ls->players)[i])->last_live;
			winner_num = i + 1;
		}
		i++;
	}
	if (ls->args->fl_visual == 0)
	{
		printf("GAME_ENDED on cycle %zu\n", ls->cycle);
		printf("The winner is: player %d, \"%s\"\n",
			winner_num, ((ls->players)[(winner_num - 1)])->name);
	}
	//free structure
#if VIZU
	if (ls->args->fl_visual == 1)
		end_draw((ls->players)[(winner_num - 1)]);
#endif
	exit(-1);
}

int					calculate_processes_and_0lives(t_proc *proc)
{
	int sum;

	sum = 0;
	while (proc)
	{
		sum++;
		proc->is_alive = FALSE;
		proc = proc->next;
	}
	return (sum);
}

int					kill_processes(t_proc **head, t_core *ls)
{
	t_proc	*ptr;
	t_proc	*tmp;

	ptr = *head;
	while (ptr)
	{
		if (ptr == *head && !(ptr->is_alive))
		{
			tmp = ptr;
			*head = ptr->next;
			ptr = *head;
			if (ls->args->num_debug & 8)
				printf("Process %zu hasn't lived for %zu cycles (CTD %zu)\n",
					tmp->number, ls->cycle - tmp->alive_at, ls->cycle_to_die);
			ft_strdel((char **)&(tmp));
		}
		else if (ptr->next && !(ptr->next->is_alive))
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			if (ls->args->num_debug & 8)
				printf("Process %zu hasn't lived for %zu cycles (CTD %zu)\n",
					tmp->number, ls->cycle - tmp->alive_at,
					ls->cycle_to_die + CYCLE_DELTA);
			ft_memdel((void **)&(tmp));
		}
		else
			ptr = ptr->next;
	}
	return (calculate_processes_and_0lives(*head));
}

void				empty_player_lives(t_core *ls)
{
	int i;

	i = 0;
	while (i < ls->num_of_players)
	{
		((ls->players)[i])->sum_lives_in_previous_period =
			((ls->players)[i])->sum_lives_in_current_period;
		((ls->players)[i])->sum_lives_in_current_period = 0;
		i++;
	}
}

void				armageddon(t_core *ls)
{
	if (ls->args->fl_dump && ls->cycle == ls->args->num_dump)
	{
		print_data(ls->field, MEM_SIZE, ls->args->width_dump);
		exit(-1);
	}
	if (ls->cycle == ls->next_cycle_to_die)
	{
		if (ls->gen_lives_in_current_period >= NBR_LIVE ||
						ls->nbr_of_checks >= MAX_CHECKS - 1)
		{
			if (ls->cycle_to_die > CYCLE_DELTA)
			{
				ls->cycle_to_die -= CYCLE_DELTA;
				if (ls->args->num_debug & 2)
					printf("Cycle to die is now %zu\n", ls->cycle_to_die);
				ls->nbr_of_checks = 0;
			}
			else
				game_end(ls);
		}
		else
			(ls->nbr_of_checks)++;
		empty_player_lives(ls);
		ls->gen_lives_in_previous_period = ls->gen_lives_in_current_period;
		ls->gen_lives_in_current_period = 0;
		ls->next_cycle_to_die = ls->cycle + ls->cycle_to_die;
		ls->num_of_processes = kill_processes(&(ls->processes_list), ls);
		if (!(ls->num_of_processes))
			game_end(ls);
	}
}

int					main(int argc, char **argv)
{
	t_core	*ls;
	t_proc	*current_process;

	ls = ft_memalloc(sizeof(t_core));
	if (argc == 1)
		vm_show_usage();
	ls->args = vm_valid(argc, argv);
	for_test(ls->args);
	vm_sort_player(ls->args);
	ls->players = ls->args->player;
	init_my_player_and_process(ls);
	// introduce()
	if (ls->args->fl_visual == 1)
		ls->args->num_debug = 0;
#if VIZU
	if (ls->args->fl_visual == 1)
		start_draw(ls);
#endif
	while (1)
	{
		if (ls->args->num_debug & 2 && ls->cycle)
			printf("It is now cycle %zu\n", ls->cycle);
		armageddon(ls);
		current_process = ls->processes_list;
		while (current_process)
		{
			if (current_process->execute_at == ls->cycle)
				opcode(ls, current_process);
			current_process = current_process->next;
		}
#if VIZU
		if (ls->args->fl_visual == 1)
			drawing(ls);
#endif
		(ls->cycle)++;
	}
	return (0);
}
