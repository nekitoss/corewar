#include "corewar.h"

#define OCTET 8
#define TRUE 1
#define FALSE 0

#define P_PAR (proc->par)
#define P_REG (proc->reg)
#define P_COD_B (proc->coding_byte)



void				f_live(t_core *ls, t_proc *proc, g_my_op *func);
void				f_ld(t_core *ls, t_proc *proc, g_my_op *func);
void				f_st(t_core *ls, t_proc *proc, g_my_op *func);
void				f_add(t_core *ls, t_proc *proc, g_my_op *func);
void				f_sub(t_core *ls, t_proc *proc, g_my_op *func);
void				f_and(t_core *ls, t_proc *proc, g_my_op *func);
void				f_or(t_core *ls, t_proc *proc, g_my_op *func);
void				f_xor(t_core *ls, t_proc *proc, g_my_op *func);
void				f_zjmp(t_core *ls, t_proc *proc, g_my_op *func);
void				f_ldi(t_core *ls, t_proc *proc, g_my_op *func);
void				f_sti(t_core *ls, t_proc *proc, g_my_op *func);
void				f_fork(t_core *ls, t_proc *proc, g_my_op *func);
void				f_lld(t_core *ls, t_proc *proc, g_my_op *func);
void				f_lldi(t_core *ls, t_proc *proc, g_my_op *func);
void				f_lfork(t_core *ls, t_proc *proc, g_my_op *func);
void				f_aff(t_core *ls, t_proc *proc, g_my_op *func);

g_my_op				tab[17] =
{
	{0,			0,	{0, 0, 0},												0,	0,		0,	0},
	{f_live,	1,	{T_DIR, 0, 0},											1,	10,		0,	4},
	{f_ld,		2,	{T_DIR | T_IND, T_REG, 0},								2,	5,		1,	4},
	{f_st,		2,	{T_REG, T_IND | T_REG, 0},								3,	5,		1,	0},
	{f_add,		3,	{T_REG, T_REG, T_REG},									4,	10,		1,	0},
	{f_sub,		3,	{T_REG, T_REG, T_REG},									5,	10,		1,	0},
	{f_and,		3,	{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},	6,	6,		1,	4},
	{f_or,		3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	7,	6,		1,	4},
	{f_xor,		3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	8,	6,		1,	4},
	{f_zjmp,	1,	{T_DIR, 0, 0},											9,	20,		0,	2},
	{f_ldi,		3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			10,	25,		1,	2},
	{f_sti,		3,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			11,	25,		1,	2},
	{f_fork,	1,	{T_DIR, 0, 0},											12,	800,	0,	2},
	{f_lld,		2,	{T_DIR | T_IND, T_REG, 0},								13,	10,		1,	4},
	{f_lldi,	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			14,	50,		1,	2},
	{f_lfork,	1,	{T_DIR, 0, 0},											15,	1000,	0,	2},
	{f_aff,		1,	{T_REG, 0, 0},											16,	2,		1,	0}
};

short				revert_16_bits_size_t(short num);
int					revert_32_bits_size_t(int num);
int					check_coding_byte(t_core *ls, t_proc *proc, g_my_op *func);
int					cmp_coding_byte(g_my_op *func, unsigned char coding_byte);
void				shift_pc(size_t *pc, unsigned int value);
int					read_parameters_and_shift(g_my_op *func, t_proc *proc);
int					read_non_conv_parameters_and_shift(g_my_op *func, t_proc *proc);
int					read_data_block(t_core *ls, unsigned int start, int len);
int					cmp_one_param(g_my_op *func, unsigned char coding_byte, int param_num);
void				add_proc_on_top(t_core *ls, unsigned int pc, int belong_to_player);
void				clone_proc(t_proc *father, t_proc *son);
// void				convert_param_to_data(g_my_op *func, t_proc *proc, int par_num);
void				convert_param_to_data(t_proc *proc, int par_num);
void				convert_param_to_data_no_idx(t_proc *proc, int par_num);
unsigned char		ident_param(unsigned char coding_byte, int param_num);
void				write_data_block(t_proc *proc, int data, unsigned int start, int len);
void				print_data(unsigned char *str, size_t len, size_t width);

//#################### funcions
void				f_live(t_core *ls, t_proc *proc, g_my_op *func)
{
	int	alive_num;
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	alive_num = read_data_block(ls, proc->pc + 1, 4);
	shift_pc(&(proc->pc), 5);
	if (alive_num < 0 && alive_num >= (ls->num_of_players * -1))
	{
		alive_num = (alive_num * (-1)) - 1;
		(((ls->players)[alive_num])->sum_lives_in_current_period)++; 
		((ls->players)[alive_num])->last_live = ls->cycle;
		if (debug) {printf("PLAYER_%d  IS ALIIIIIIIIVE!\n", (alive_num + 1) * -1);}
	}

	(ls->gen_lives_in_current_period)++;
	proc->is_alive = TRUE;
	if (debug) {printf("-end_of_try_execute f_live at cycle=%zu\n", ls->cycle);}
}

void				f_ld(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
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
	}
	if (debug) {printf("-end_of_try_execute f_ld at cycle=%zu\n", ls->cycle);}
}

void				f_st(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data(proc, 0);
		what = P_PAR[0];
		convert_param_to_data(proc, 1);
		where = ((P_PAR[1] % IDX_MOD) + (int)proc->old_pc) % MEM_SIZE;
		// print_data(ls->field, MEM_SIZE, 64);
		write_data_block(proc, what, where, 4);
	}
	if (debug) {printf("-end_of_try_execute f_st at cycle=%zu\n", ls->cycle);}
// print_data(ls->field, MEM_SIZE, 64);
}

void				f_add(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
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
	if (debug) {printf("-end_of_try_execute f_add at cycle=%zu\n", ls->cycle);}
}

void				f_sub(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
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
	if (debug) {printf("-end_of_try_execute f_sub at cycle=%zu\n", ls->cycle);}
}

void				f_and(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
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
	}
	if (debug) {printf("-end_of_try_execute f_and at cycle=%zu\n", ls->cycle);}
}

void				f_or(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
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
	}
	if (debug) {printf("-end_of_try_execute f_or at cycle=%zu\n", ls->cycle);}
}

void				f_xor(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
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
	}
	if (debug) {printf("-end_of_try_execute f_xor at cycle=%zu\n", ls->cycle);}
}

void				f_zjmp(t_core *ls, t_proc *proc, g_my_op *func)
{
	int where;

	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	if (proc->carry)
	{
		where = read_data_block(ls, proc->pc + 1, 2);
		shift_pc(&(proc->pc), where);
	}
	if (debug) {printf("-end_of_try_execute f_zjmp at cycle=%zu\n", ls->cycle);}
}

void				f_ldi(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data(proc, 0);
		convert_param_to_data(proc, 1);
		what = read_data_block(ls ,(P_PAR[0] + P_PAR[1]), 4);
		where = P_PAR[2];
		P_REG[where] = what;
	}
	if (debug) {printf("-end_of_try_execute f_ldi at cycle=%zu\n", ls->cycle);}
}

void				f_sti(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		what = P_REG[P_PAR[0]];
		convert_param_to_data(proc, 1);
		convert_param_to_data(proc, 2);
		where = (((P_PAR[1] + P_PAR[2]) % IDX_MOD) + (int)proc->old_pc) % MEM_SIZE;
		// print_data(ls->field, MEM_SIZE, 64);
		write_data_block(proc, what, where, 4);
	}
if (debug) {printf("-end_of_try_execute f_sti at cycle=%zu\n", ls->cycle);}
// print_data(ls->field, MEM_SIZE, 64);
}

void				f_fork(t_core *ls, t_proc *proc, g_my_op *func)
{
	int where;

	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	where = read_data_block(ls, proc->pc + 1, 2);
	where = ((int)proc->pc + where) % IDX_MOD;
	add_proc_on_top(ls, where, proc->belong_to_player);
	clone_proc(proc, ls->processes_list);
	if (debug) {printf("-end_of_try_execute f_fork at cycle=%zu\n", ls->cycle);}
}

void				f_lld(t_core *ls, t_proc *proc, g_my_op *func)
{//no idxmod
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data_no_idx(proc, 0);
		what = P_PAR[0];
		where = P_PAR[1];
		P_REG[where] = what;
		if (!what)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	if (debug) {printf("-end_of_try_execute f_lld at cycle=%zu\n", ls->cycle);}
}

void				f_lldi(t_core *ls, t_proc *proc, g_my_op *func)
{//no idxmod
	int what;
	int where;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		convert_param_to_data_no_idx(proc, 0);
		convert_param_to_data_no_idx(proc, 1);
		what = read_data_block(ls ,(P_PAR[0] + P_PAR[1]), 4);
		where = P_PAR[2];
		P_REG[where] = what;
	}
	if (debug) {printf("-end_of_try_execute f_lldi at cycle=%zu\n", ls->cycle);}
}

void				f_lfork(t_core *ls, t_proc *proc, g_my_op *func)
{//no idxmod
	int where;

	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	where = read_data_block(ls, proc->pc + 1, 2);
	where = (int)proc->pc + where;
	add_proc_on_top(ls, where, proc->belong_to_player);
	clone_proc(proc, ls->processes_list);
	if (debug) {printf("-end_of_try_execute f_lfork at cycle=%zu\n", ls->cycle);}
}

void				f_aff(t_core *ls, t_proc *proc, g_my_op *func)
{
	int what;

	P_COD_B = read_data_block(ls, proc->pc + 1, 1);
	if (debug) {printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);}
	shift_pc(&(proc->pc), 2);
	if (read_non_conv_parameters_and_shift(func, proc))
	{
		what = P_REG[P_PAR[0]] % 256;
		if (debug) {printf("### ICANDO AFF ####\n");
		printf("%c\n", what);}
	}
	if (debug) {printf("-end_of_try_execute f_aff at cycle=%zu\n", ls->cycle);}
}

//#################### funcions

void					my_deb(char *str)
{
	ft_putstr_fd(str, 2);
	exit(-1);
}

// void					convert_param_to_data(g_my_op *func, t_proc *proc, int par_num)
void					convert_param_to_data(t_proc *proc, int par_num)
{
	int coding_byte;

	coding_byte = ident_param(P_COD_B, par_num);
	if (coding_byte & T_REG)
		P_PAR[par_num] = (int)(P_REG[(P_PAR[par_num])]); //тут может быть ошибка неправильного регистра
	else if (coding_byte & T_IND)
	{
		P_PAR[par_num] = ((P_PAR[par_num] % IDX_MOD) + (int)proc->old_pc) % MEM_SIZE;
		P_PAR[par_num] = (int)read_data_block(proc->ls, P_PAR[par_num], 4);
	}
	// else if ((coding_byte & T_DIR) && func->bytes_for_tdir == 2)
	// 	P_PAR[par_num] = (int)((short)P_PAR[par_num]);
}

void					convert_param_to_data_no_idx(t_proc *proc, int par_num)
{
	int coding_byte;

	coding_byte = ident_param(P_COD_B, par_num);
	if (coding_byte & T_REG)
		P_PAR[par_num] = (int)(P_REG[(P_PAR[par_num])]); //тут может быть ошибка неправильного регистра
	else if (coding_byte & T_IND)
	{
		P_PAR[par_num] = (P_PAR[par_num] + (int)proc->old_pc) % MEM_SIZE;
		P_PAR[par_num] = (int)read_data_block(proc->ls, P_PAR[par_num], 4);
	}
	// else if ((coding_byte & T_DIR) && func->bytes_for_tdir == 2)
	// 	P_PAR[par_num] = (int)((short)P_PAR[par_num]);
}

unsigned char		ident_param(unsigned char coding_byte, int param_num)
{
	coding_byte = (coding_byte & (0b11 << ((3 - param_num) * 2))) >> ((3 - param_num) * 2);
	if (coding_byte == 3)
		coding_byte = 4;
	return (coding_byte);
}

int					calculate_pc_shift(g_my_op *func, unsigned char coding_byte, int par_num)
{
	coding_byte = ident_param(coding_byte, par_num);
// printf("calculate_pc_shift = par%d=%02x\n", i, coding_byte);
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



int					read_parameters_and_shift(g_my_op *func, t_proc *proc)
{
	int			i;
	int			correct_params;

	correct_params = 1;
	i = 0;
	while (i < func->num_of_params)
	{
		P_PAR[i] = (int)read_data_block(proc->ls, proc->pc, calculate_pc_shift(func, P_COD_B, i));
		if (cmp_one_param(func, P_COD_B, i))
		{
			if ((ident_param(P_COD_B, i) & T_REG) && P_PAR[i] > 0 && P_PAR[i] < 17)
				P_PAR[i] = (int)((short)P_REG[(P_PAR[i])]);
			else if (ident_param(P_COD_B, i) & T_IND)
			{
				P_PAR[i] = (int)(((short)P_PAR[i]) % IDX_MOD);
				P_PAR[i] = (int)read_data_block(proc->ls, proc->pc, P_PAR[i]);
			}
			else if ((ident_param(P_COD_B, i) & T_DIR) && func->bytes_for_tdir == 2)
				P_PAR[i] = (int)((short)P_PAR[i]);
			else if ((ident_param(P_COD_B, i) & T_DIR) && func->bytes_for_tdir == 4)
				continue ;
			else
				correct_params = 0;
		}
		else
			correct_params = 0;
		i++;
	}
	return (correct_params);
}

int					read_non_conv_parameters_and_shift(g_my_op *func, t_proc *proc)
{
	int			i;
	int			correct_params;

	correct_params = 1;
	i = 0;
	while (i < func->num_of_params)
	{
		P_PAR[i] = (int)read_data_block(proc->ls, proc->pc, calculate_pc_shift(func, P_COD_B, i));
		if (cmp_one_param(func, P_COD_B, i))
		{
			if ((ident_param(P_COD_B, i) & T_REG) && P_PAR[i] < 1 && P_PAR[i] > 16)
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

void				write_data_block(t_proc *proc, int data, unsigned int start, int len)
{
	int i;

	i = 0;
	if (len == 4)
		data = revert_32_bits_size_t(data);
	else if (len == 2)
		data = revert_16_bits_size_t(data);
	while (i < len && i < 5)
	{
		// int where = ((start + i + MEM_SIZE) % MEM_SIZE);
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
	// res = revert_16_bits_size_t(res);
	
	return (res);
}

int					read_4_byte(t_core *ls, unsigned int start)
{
	int 	res;

	res = ls->field[(start % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 1) % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 2) % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 3) % MEM_SIZE)];
	// res = revert_32_bits_size_t(res);
	return (res);
}

// size_t				read_data_block(t_core *ls, size_t start, int len)
// {
// 	int i;
// 	size_t mem_block;

// 	mem_block = 0;
// 	i = 0;
// 	while (i < len && i < 9)
// 	{
// 		mem_block = mem_block << OCTET;
// 		mem_block |= ls->field[((start + i) % MEM_SIZE)];
// 		i++;
// 	}
// 	if (len == 4)
// 		mem_block = revert_32_bits_size_t(mem_block);
// 	else if (len == 2)
// 		mem_block = revert_16_bits_size_t(mem_block);
// 	return (mem_block);
// }

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
	else
		my_deb("wrong len in read data block");
	return (res);
}

short				revert_16_bits_size_t(short num)
{
	num = (num >> 8) | (num << 8);
	return (num);
}

int					revert_32_bits_size_t(int num)
{
	num = ((num >> 24) & 0xff) | // move byte 3 to byte 0
			((num << 8) & 0xff0000) | // move byte 1 to byte 2
			((num >> 8) & 0xff00) | // move byte 2 to byte 1
			((num << 24) & 0xff000000); // byte 0 to byte 3
	return (num);
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
	// printf("counter = %4zu\n", *pc);
}

void				set_next_ex(size_t *next_execution_at, int value)
{
	(*next_execution_at) = (*next_execution_at) + value;
	// printf("set_next execution at = %4zu\n", *pc);
}
void				my_read_code(t_core *ls)
{
	int fd = open("/nfs/2016/m/mpochuka/pool/corewar/src/test.cor", O_RDONLY);
	size_t file_size = lseek(fd, 0, SEEK_END);
	size_t offset = lseek(fd, 4 + PROG_NAME_LENGTH + 1 + 3 + sizeof(int) + COMMENT_LENGTH + 1 + 3, 0);
	
	unsigned char *tmp;
	size_t code_len = file_size - offset;
	tmp = (unsigned char *)ft_strnew(code_len);
	read (fd, tmp, code_len);
if (debug) {printf("file_size=%zu; offset=%zu; len=%zu\n", file_size, offset, code_len);}
	close(fd);

	if (debug) {print_data(tmp, code_len, 32);}

	((ls->players)[0])->program_code = tmp;
}

void				init_my_player_and_process(t_core *ls)
{
	int i = 0;
	
	ls->num_of_players = ls->args->cnt_player;
	ls->cycle_to_die = CYCLE_TO_DIE;
	ls->next_cycle_to_die = ls->cycle_to_die;
	
	// my_read_code(ls);

	while (i < ls->num_of_players)
	{
		add_proc_on_top(ls, (i * (MEM_SIZE / ls->num_of_players)), ((ls->players)[i])->num);
		ft_memcpy((ls->field), ((ls->players)[i])->program_code, ((ls->players)[i])->size_code);
		i++;
	}
	
	// ls->processes_list->reg[1] = 65;
	ls->num_of_processes = ls->num_of_players;
	// printf("end of init\n\n");

	// print_data(ls->field, MEM_SIZE, 64);
}



void				opcode(t_core *ls, t_proc *proc)
{
	unsigned char opcode;

	if (proc->opcode_to_execute < 17 && proc->opcode_to_execute > 0)
	{
		proc->old_pc = proc->pc;
		((tab[(proc->opcode_to_execute)]).func)(ls, proc, &(tab[(proc->opcode_to_execute)]));
		// shift_pc(&(proc->pc), (tab[(proc->opcode_to_execute)]).cycles_to_exec);
		// shift_pc(&(proc->pc), 1);
	}
	else
	{
// printf("incorrect opcode\n");
		// shift_pc(&(proc->pc), 1);
	}
	opcode = read_data_block(ls, proc->pc, 1);
// printf("opcode=%d=%#02x\n", opcode, opcode);
	proc->opcode_to_execute = opcode;
	if (opcode < 17 && opcode > 0)
	{
		proc->execute_at = ls->cycle + (tab[opcode]).cycles_to_exec;
	}
	else
	{
		proc->execute_at = ls->cycle + 1;
		shift_pc(&(proc->pc), 1);
	}
}

int					check_coding_byte(t_core *ls, t_proc *proc, g_my_op *func)
{
	unsigned char coding_byte;
	
	coding_byte = read_data_block(ls, proc->pc + 1, 1);
// printf("coding_par byte=%u=%#x\n", coding_byte, (coding_byte));
	if ((cmp_coding_byte(func, coding_byte)))
	{
// printf("params are OK\n");
		return (1);
	}
// printf("wrong parameters for %03d opcode\n", proc->opcode_to_execute);
	// shift_pc(&(proc->pc), 1);
	return (0);

}

int					cmp_coding_byte(g_my_op *func, unsigned char coding_byte)
{
	unsigned char par;

	if (func->num_of_params >= 1)
	{
		par = ident_param(coding_byte, 0);
		if (!(par & func->type_of_params[0]))
			return (0);
	}
	if (func->num_of_params >= 2)
	{
		par = ident_param(coding_byte, 1);
		if (!(par & func->type_of_params[1]))
			return (0);
	}
	if (func->num_of_params == 3)
	{
		par = ident_param(coding_byte, 2);
		if (!(par & func->type_of_params[2]))
			return (0);
	}
	return (1);
}

int					cmp_one_param(g_my_op *func, unsigned char coding_byte, int param_num)
{
	if (ident_param(coding_byte, param_num) & func->type_of_params[param_num])
			return (1);
	return (0);
}

void				add_proc_on_top(t_core *ls, unsigned int pc, int belong_to_player)
{
	t_proc	*new;

	new = ft_memalloc(sizeof(t_proc));
	new->reg[1] = belong_to_player;
	new->next = ls->processes_list;
	new->pc = pc;
	new->belong_to_player = belong_to_player;
	new->ls = ls;
	new->execute_at = ls->cycle;
	ls->processes_list = new;
}

void				clone_proc(t_proc *father, t_proc *son)
{
	if (father && son)
	{
		ft_memcpy(son->reg, father->reg, (REG_NUMBER + 1) * sizeof(*(father->reg)));
		son->is_alive = father->is_alive;
		son->carry = father->carry;
		son->execute_at = father->ls->cycle + 1;
		// son->opcode = read_data_block(father->ls, son->pc, 1);
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
	while(i < ls->num_of_players)
	{
		if ((ssize_t)(((ls->players)[i])->last_live) > last_live_of_winner) //не факт что больше равно
		{
			last_live_of_winner = ((ls->players)[i])->last_live;
			winner_num = i + 1;
		}
		i++;
	}//можно сделать указание что игрок выиграл не сказав лайв сплясать от макс чекс
	if (debug) {printf("GAME_ENDED on cycle %zu\n", ls->cycle);
	printf("The winner is: player %d, \"%s\"\n", winner_num, ((ls->players)[(winner_num - 1)])->name);}
	//free structure
	exit (-1);
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

int					kill_processes(t_proc **head)
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
			ft_strdel((char **)&(tmp));
		}
		else if (ptr->next && !(ptr->next->is_alive))
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			ft_strdel((char **)&(tmp));
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
		((ls->players)[i])->sum_lives_in_current_period = 0;
		((ls->players)[i])->sum_lives_in_previous_period = ((ls->players)[i])->sum_lives_in_current_period;
		i++;
	}
}

void				armageddon(t_core *ls)
{
	if (ls->args->fl_dump && ls->cycle == ls->args->num_dump)
		print_data(ls->field, MEM_SIZE, ls->args->width_dump);
	if (ls->cycle == ls->next_cycle_to_die)
	{
		if (ls->gen_lives_in_current_period >= NBR_LIVE || ls->nbr_of_checks >= MAX_CHECKS)
		{
			if (ls->cycle_to_die > CYCLE_DELTA)
			{
				ls->cycle_to_die -= CYCLE_DELTA;
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
		ls->num_of_processes = kill_processes(&(ls->processes_list));
		if (!(ls->num_of_processes))
			game_end(ls);
	}
}

int					main(int argc, char **argv)
{
	t_core	*ls;
	t_proc	*current_process;

	ls = ft_memalloc(sizeof(t_core));

	if(argc == 1)
		vm_show_usage();
	ls->args = vm_valid(argc, argv);
	vm_sort_player(ls->args);
	for_test(ls->args);
	// if (ls->args->fl_visual == 1)// turn on fl_visual
	// {
	// 	start_draw(ls->args);
	// 	end_draw();
	// }


// printf("MEM_SIZE=%d\n", MEM_SIZE);
	ls->players = ls->args->player;
	
	// init_my_player_and_process(ls);
	return(10);

	//call visio
	while (1)
	{
		// printf("cycle=%06zu\n", ls->cycle);
		current_process =  ls->processes_list;
		armageddon(ls);
		while (current_process)
		{
			if (current_process->execute_at == ls->cycle)
				opcode(ls, current_process);
			current_process = current_process->next;
		}
		//call visio
		(ls->cycle)++;
	}

	return (0);
}
