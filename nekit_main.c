#include "corewar.h"

#define OCTET 8

typedef struct		s_proc
{
	size_t			pc;
	int				reg[REG_NUMBER + 1];
	int				live;
	char			carry;
	size_t			next_execution_at;
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
	int				cycles_per_second;
	char			paused;
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
int					coding_byte(t_core *ls, t_proc *proc, t_my_op *func);
int					check_coding_byte(t_my_op *func, unsigned char coding_byte);


//#################### funcions
void				f_live(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);

}

void				f_ld(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_st(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_add(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_sub(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_and(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_or(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_xor(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_zjmp(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);

}

void				f_ldi(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_sti(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_fork(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);

}

void				f_lld(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_lldi(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

void				f_lfork(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);

}

void				f_aff(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (coding_byte(ls, proc, func))
	{

	}
}

//#################### funcions
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
	// (*next_execution_at) = (*next_execution_at) % MEM_SIZE;
	// printf("counter = %4zu\n", *pc);
}

void				init_my_player_and_process(t_core *ls)
{
	ls->num_of_players = 1;
	ls->players = (t_player **)ft_memalloc(sizeof(t_player *) * ls->num_of_players);
	(ls->players)[0] = (t_player *)ft_memalloc(sizeof(t_player));
	((ls->players)[0])->name = ft_strdup("my_name");
	(ls->players)[0]->comment = ft_strdup("some_unusefull comment");
	(ls->players)[0]->num = -1;

	ls->processes_list = ft_memalloc(sizeof(t_proc));
	ls->processes_list->reg[1] = -1;
}

void				opcode(t_core *ls, t_proc *proc)
{
	unsigned char opcode;

	opcode = read_data_block(ls, proc->pc, 1);
	printf("opcode = %d\n", opcode);
	shift_pc(&(proc->pc), 1);
	if (opcode < 17 && opcode > 0)
	{
		((op_tab[opcode]).func)(ls, ls->processes_list, &(op_tab[opcode]));
		// coding_byte(ls, ls->processes_list);
	}
	else
		printf("incorrect opcode\n");

}

int					coding_byte(t_core *ls, t_proc *proc, t_my_op *func)
{
	unsigned char coding_byte;
	coding_byte = read_data_block(ls, proc->pc, 1);
	printf("coding byte_int=%u, codingbyte_hex=%#x\n", coding_byte, (coding_byte));// & 0b11000000));
	if ((check_coding_byte(func, coding_byte)))
	{
		printf("params are OK\n");

		
		
		return (1);
	}
	printf("wrong parameters for this opcode\n");
	// shift_pc(&(proc->pc), 1);
	return (0);

}

int					check_coding_byte(t_my_op *func, unsigned char coding_byte)
{
	char par;

	par = 0;
	if (func->num_of_params >= 1)
	{
		par = (coding_byte & 0b11000000) >> (6);
		printf("par1=%02x\n", par);
		if (par == 3)
			par = 4;
		if (!(par & func->type_of_params[0]))
			return (0);
	}
	if (func->num_of_params >= 2)
	{
		par = (coding_byte & 0b110000) >> (4);
		printf("par2=%02x\n", par);
		if (par == 3)
			par = 4;
		if (!(par & func->type_of_params[1]))
			return (0);
	}
	if (func->num_of_params == 3)
	{
		par = (coding_byte & 0b1100) >> (2);
		printf("par3=%02x\n", par);
		if (par == 3)
			par = 4;
		if (!(par & func->type_of_params[2]))
			return (0);
	}
	return (1);
}

int					main(void)
{
	t_core	*ls;

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
	
	opcode(ls, ls->processes_list);
	
	
	// unsigned int par1;
	// par1 = read_data_block(ls, (ls->processes_list->pc), 4);
	// shift_pc(&(ls->processes_list->pc), 4);
	// printf("par1_hex=%#x; %u\n", par1, par1%MEM_SIZE);

	// unsigned int par2;

	// par2 = read_data_block(ls, (ls->processes_list->pc), 1);
	// shift_pc(&(ls->processes_list->pc), 1);
	// printf("par2_hex=%#x; %u\n", par2, par2%MEM_SIZE);


	return (0);
}