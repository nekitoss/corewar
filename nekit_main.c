#include "corewar.h"

#define OCTET 8

typedef struct		s_proc
{
	size_t			pc;
	int				reg[REG_NUMBER + 1];
	int				is_alive;
	char			carry;
	size_t			execute_at;
	int				opcode_to_execute;
	int				wrong_params;
	struct s_core	*ls;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_player
{
	char			*name;
	char			*comment;
	unsigned char	*program_code;
	size_t			last_live;
	unsigned int	sum_lives;
	int				num;
	int				code_size;
}					t_player;

typedef struct		s_core
{
	size_t			cycle;
	size_t			gen_lives_in_current_period;
	size_t			cycle_to_die;
	t_player		**players; //покачто хард-код
	int				num_of_players;
	int				num_of_processes;
	unsigned char	field[MEM_SIZE];
	t_proc			*processes_list;
}					t_core;



typedef struct		s_my_op
{
	void			(*func)(t_core *ls, t_proc *proc, struct s_my_op *func);
	char			num_of_params;
	char			type_of_params[3];
	char			function_num;
	int				cycles_to_exec;
	char			is_codage;
	char			bytes_for_tdir;
}					t_my_op;

void				f_live(t_core *ls, t_proc *proc, t_my_op *func);
void				f_ld(t_core *ls, t_proc *proc, t_my_op *func);
void				f_st(t_core *ls, t_proc *proc, t_my_op *func);
void				f_add(t_core *ls, t_proc *proc, t_my_op *func);
void				f_sub(t_core *ls, t_proc *proc, t_my_op *func);
void				f_and(t_core *ls, t_proc *proc, t_my_op *func);
void				f_or(t_core *ls, t_proc *proc, t_my_op *func);
void				f_xor(t_core *ls, t_proc *proc, t_my_op *func);
void				f_zjmp(t_core *ls, t_proc *proc, t_my_op *func);
void				f_ldi(t_core *ls, t_proc *proc, t_my_op *func);
void				f_sti(t_core *ls, t_proc *proc, t_my_op *func);
void				f_fork(t_core *ls, t_proc *proc, t_my_op *func);
void				f_lld(t_core *ls, t_proc *proc, t_my_op *func);
void				f_lldi(t_core *ls, t_proc *proc, t_my_op *func);
void				f_lfork(t_core *ls, t_proc *proc, t_my_op *func);
void				f_aff(t_core *ls, t_proc *proc, t_my_op *func);

t_my_op				op_tab[17] =
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



size_t				revert_16_bits_size_t(size_t num);
size_t				revert_32_bits_size_t(size_t num);
int					check_coding_byte(t_core *ls, t_proc *proc, t_my_op *func);
int					cmp_coding_byte(t_my_op *func, unsigned char coding_byte);
void				shift_pc(size_t *pc, int value);
void				read_parameters_and_shift(t_my_op *func, t_proc *proc, unsigned char coding_byte, int ret[]);
size_t				read_data_block(t_core *ls, size_t start, int len);
int					cmp_one_param(t_my_op *func, unsigned char coding_byte, int param_num);

//#################### funcions
void				f_live(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	printf("end_of_try_execute f_live at cycle=%zu\n", ls->cycle);
}

void				f_ld(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_ld at cycle=%zu\n", ls->cycle);
}

void				f_st(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_st at cycle=%zu\n", ls->cycle);
}

void				f_add(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_add at cycle=%zu\n", ls->cycle);
}

void				f_sub(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_sub at cycle=%zu\n", ls->cycle);
}

void				f_and(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_and at cycle=%zu\n", ls->cycle);
}

void				f_or(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_or at cycle=%zu\n", ls->cycle);
}

void				f_xor(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_xor at cycle=%zu\n", ls->cycle);
}

void				f_zjmp(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	printf("end_of_try_execute f_zjmp at cycle=%zu\n", ls->cycle);
}

void				f_ldi(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_ldi at cycle=%zu\n", ls->cycle);
}

void				f_sti(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_sti at cycle=%zu\n", ls->cycle);
}

void				f_fork(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	printf("end_of_try_execute f_fork at cycle=%zu\n", ls->cycle);
}

void				f_lld(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_lld at cycle=%zu\n", ls->cycle);
}

void				f_lldi(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("end_of_try_execute f_lldi at cycle=%zu\n", ls->cycle);
}

void				f_lfork(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	printf("end_of_try_execute f_lfork at cycle=%zu\n", ls->cycle);
}

void				f_aff(t_core *ls, t_proc *proc, t_my_op *func)
{
	int par[1];
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	shift_pc(&(proc->pc), 2);
	read_parameters_and_shift(func, proc, read_data_block(ls, proc->pc - 1, 1), par);
	if (!(proc->wrong_params))
	{
		printf("### ICANDO AFF ####\n");
		printf("%c\n", par[0] % 256);
	}
	else
	{
		proc->execute_at = ls->cycle + 1;
		printf("AFF parametrs WRONg, CAN't DO aff\n");
	}
	printf("end_of_try_execute f_aff at cycle=%zu\n", ls->cycle);
}

//#################### funcions

unsigned char		ident_param(unsigned char coding_byte, int param_num)
{
	coding_byte = (coding_byte & (0b11 << ((3 - param_num) * 2))) >> ((3 - param_num) * 2);
	if (coding_byte == 3)
		coding_byte = 4;
	return (coding_byte);
}

int					calculate_pc_shift(t_my_op *func, unsigned char coding_byte, int par_num)
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

void				read_parameters_and_shift(t_my_op *func, t_proc *proc, unsigned char coding_byte, int ret[])
{
	int			i;

	i = 0;
	while (i < func->num_of_params)
	{
		ret[i] = (int)read_data_block(proc->ls, proc->pc, calculate_pc_shift(func, coding_byte, i));
		if (cmp_one_param(func, coding_byte, i))
		{
			if ((ident_param(coding_byte, i) & T_REG) && ret[i] > 0 && ret[i] < 17)
				ret[i] = (int)((short)(proc->reg)[(ret[i])]);
			else if (ident_param(coding_byte, i) & T_IND)
			{
				ret[i] = (int)(((short)ret[i]) % IDX_MOD);
				ret[i] = (int)read_data_block(proc->ls, proc->pc, ret[i]);
			}
			else if ((ident_param(coding_byte, i) & T_DIR) && func->bytes_for_tdir == 2)
				ret[i] = (int)((short)ret[i]);
			else if ((ident_param(coding_byte, i) & T_DIR) && func->bytes_for_tdir == 4)
				continue ;
			else
				proc->wrong_params = 1;
		}
		else
			proc->wrong_params = 1;
		i++;
	}
}

// int					read_parameter(t_my_op *func, t_proc *proc, unsigned char coding_byte, int par_num)
// {
// 	int			res;

// 	res = 0;
// 	coding_byte = ident_param(coding_byte, par_num);
// 	if (coding_byte & T_REG)
// 	{
// 		res = read_data_block(proc->ls, proc->pc, 2);
// 		if (res > 0 && res < 17)
// 			res = (short int)((proc->reg)[]);
// 	}
// 	else if (coding_byte & T_IND)
// 		res = (int)(read_data_block(proc->ls, proc->pc, 4));
// 	else if (coding_byte & T_DIR)
// 	{
// 		if (func->bytes_for_tdir == 2)
// 			res += 2;
// 		else
// 			res += 4;
// 	}
// }

size_t				read_data_block(t_core *ls, size_t start, int len)
{
	int i;
	size_t mem_block;

	mem_block = 0;
	i = 0;
	while (i < len)
	{
		mem_block = mem_block << OCTET;
		mem_block |= ls->field[((start + i) % MEM_SIZE)];
		i++;
	}
	if (len == 4)
		mem_block = revert_32_bits_size_t(mem_block);
	else if (len == 2)
		mem_block = revert_16_bits_size_t(mem_block);
	return (mem_block);
}

size_t				revert_16_bits_size_t(size_t num)
{
	num = (num >> 8) | (num << 8);
	return (num);
}


size_t				revert_32_bits_size_t(size_t num)
{
	num = ((num >> 24) & 0xff) | // move byte 3 to byte 0
			((num << 8) & 0xff0000) | // move byte 1 to byte 2
			((num >> 8) & 0xff00) | // move byte 2 to byte 1
			((num << 24) & 0xff000000); // byte 0 to byte 3
	return (num);
}

void				print_data(unsigned char *str, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (i % 32 == 0 && i != 0)
			printf("\n");
		printf(" %02x", str[(i % MEM_SIZE)]);
		
		i++;
	}
	printf("\n");
}

void				shift_pc(size_t *pc, int value)
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

void				init_my_player_and_process(t_core *ls)
{
	ls->num_of_players = 1;
	ls->players = (t_player **)ft_memalloc(sizeof(t_player *) * ls->num_of_players);
	(ls->players)[0] = (t_player *)ft_memalloc(sizeof(t_player));
	((ls->players)[0])->name = ft_strdup("my_name");
	(ls->players)[0]->comment = ft_strdup("some_unusefull comment");
	(ls->players)[0]->num = -1;
	ls->cycle_to_die = CYCLE_TO_DIE;

	ls->processes_list = ft_memalloc(sizeof(t_proc));
	ls->processes_list->reg[1] = 65;
	ls->processes_list->ls = ls;
}

void				opcode(t_core *ls, t_proc *proc)
{
	unsigned char opcode;

	if (proc->opcode_to_execute < 17 && proc->opcode_to_execute > 0)
	{
		((op_tab[(proc->opcode_to_execute)]).func)(ls, proc, &(op_tab[(proc->opcode_to_execute)]));
		shift_pc(&(proc->pc), (op_tab[(proc->opcode_to_execute)]).cycles_to_exec);
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
		proc->execute_at = ls->cycle + (op_tab[opcode]).cycles_to_exec;
	}
	else
	{
		proc->execute_at = ls->cycle + 1;
		shift_pc(&(proc->pc), 1);
	}
}

// int					calculate_data_shift(t_my_op *func, unsigned char coding_byte)
// {
// 	int				i;
// 	int				res;
// 	unsigned char	par;

// 	par = 0;
// 	res = 0;
// 	i = 0;
// 	while (i < func->num_of_params)
// 	{
// 		par = ident_param(coding_byte, i);
// // printf("calculate_shift = par%d=%02x\n", i,par);
// 		if (par & T_REG)
// 			res += 1;
// 		else if (par & T_IND)
// 			res += 2;
// 		else if (par & T_DIR)
// 		{
// 			if (func->bytes_for_tdir == 2)
// 				res += 2;
// 			else
// 				res += 4;
// 		}
// 		i++;
// 	}
// 	return (res);
// }

int					check_coding_byte(t_core *ls, t_proc *proc, t_my_op *func)
{
	unsigned char coding_byte;
	
	coding_byte = read_data_block(ls, proc->pc + 1, 1);
printf("coding_par byte=%u=%#x\n", coding_byte, (coding_byte));// & 0b11000000));
	if ((cmp_coding_byte(func, coding_byte)))
	{
printf("params are OK\n");
		return (1);
	}
printf("wrong parameters for %03d opcode\n", proc->opcode_to_execute);
	// shift_pc(&(proc->pc), 1);
	return (0);

}

int					cmp_coding_byte(t_my_op *func, unsigned char coding_byte)
{
	unsigned char par;

	par = 0;
	if (func->num_of_params >= 1)
	{
		par = ident_param(coding_byte, 0);
// printf("par1=%02x\n", par);
		if (!(par & func->type_of_params[0]))
			return (0);
	}
	if (func->num_of_params >= 2)
	{
		par = ident_param(coding_byte, 1);
// printf("par2=%02x\n", par);
		if (!(par & func->type_of_params[1]))
			return (0);
	}
	if (func->num_of_params == 3)
	{
		par = ident_param(coding_byte, 2);
// printf("par3=%02x\n", par);
		if (!(par & func->type_of_params[2]))
			return (0);
	}
	return (1);
}

int					cmp_one_param(t_my_op *func, unsigned char coding_byte, int param_num)
{
	if (ident_param(coding_byte, param_num) & func->type_of_params[param_num])
			return (1);
	return (0);
}

int					main(void)
{
	t_core	*ls;
	t_proc	*current_process;

printf("MEM_SIZE=%d\n", MEM_SIZE);

	ls = ft_memalloc(sizeof(t_core));
	init_my_player_and_process(ls);
	
	int fd = open("/nfs/2016/m/mpochuka/pool/corewar/src/test.cor", O_RDONLY);
	size_t file_size = lseek(fd, 0, SEEK_END);
	size_t offset = lseek(fd, 4 + PROG_NAME_LENGTH + 1 + 3 + sizeof(int) + COMMENT_LENGTH + 1 + 3, 0);
	
	unsigned char *tmp;
	size_t code_len = file_size - offset;
	tmp = (unsigned char *)ft_strnew(code_len);
	read (fd, tmp, code_len);
printf("file_size=%zu; offset=%zu; len=%zu\n", file_size, offset, code_len);
	close(fd);

	ft_memcpy((void **)&((ls->field)[(ls->processes_list->pc)]), tmp, code_len);
	print_data(tmp, code_len);
	ft_strdel((char **)&tmp);
	print_data(ls->field, 32);

	while (ls->cycle < 10)//ls->cycle_to_die)
	{
		//if == ctd then check dead
		current_process =  ls->processes_list;
		while (current_process)
		{	
			if (current_process->execute_at == ls->cycle)
				opcode(ls, current_process);
			current_process = current_process->next;
		}
		(ls->cycle)++;
	}

	return (0);
}