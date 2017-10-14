#include "corewar.h"

#define OCTET 8
#define TRUE 1
#define FALSE 0


typedef struct		s_proc
{
	size_t			pc;
	int				reg[REG_NUMBER + 1];
	int				is_alive;
	char			carry;
	size_t			execute_at;
	int				opcode_to_execute;
	int				wrong_params;
	int				belong_to_player;
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
	size_t			next_cycle_to_die;
	size_t			nbr_of_checks;
	t_player		**players; //покачто хард-код
	int				num_of_players;
	int				num_of_processes;
	unsigned char	field[MEM_SIZE];
	unsigned char	colors[MEM_SIZE];
	t_proc			*processes_list;
	// t_arg			*args;
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
void				add_proc_on_top(t_core *ls, int pc, int belong_to_player);
void				clone_proc(t_proc *father, t_proc *son);

//#################### funcions
void				f_live(t_core *ls, t_proc *proc, t_my_op *func)
{
	int	alive_num;
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	alive_num = (int)read_data_block(ls, proc->pc, 4);
	shift_pc(&(proc->pc), 4);
	printf("PLAYER_%d  IS ALIIIIIIIIVE!\n", alive_num);
	proc->is_alive = TRUE;
	printf("-end_of_try_execute f_live at cycle=%zu\n", ls->cycle);
}

void				f_ld(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_ld at cycle=%zu\n", ls->cycle);
}

void				f_st(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_st at cycle=%zu\n", ls->cycle);
}

void				f_add(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_add at cycle=%zu\n", ls->cycle);
}

void				f_sub(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_sub at cycle=%zu\n", ls->cycle);
}

void				f_and(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_and at cycle=%zu\n", ls->cycle);
}

void				f_or(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_or at cycle=%zu\n", ls->cycle);
}

void				f_xor(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_xor at cycle=%zu\n", ls->cycle);
}

void				f_zjmp(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	printf("-end_of_try_execute f_zjmp at cycle=%zu\n", ls->cycle);
}

void				f_ldi(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_ldi at cycle=%zu\n", ls->cycle);
}

void				f_sti(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_sti at cycle=%zu\n", ls->cycle);
}

void				f_fork(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);

	printf("-end_of_try_execute f_fork at cycle=%zu\n", ls->cycle);
}

void				f_lld(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_lld at cycle=%zu\n", ls->cycle);
}

void				f_lldi(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	if (check_coding_byte(ls, proc, func))
	{

	}
	printf("-end_of_try_execute f_lldi at cycle=%zu\n", ls->cycle);
}

void				f_lfork(t_core *ls, t_proc *proc, t_my_op *func)
{
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
	printf("-end_of_try_execute f_lfork at cycle=%zu\n", ls->cycle);
}

void				f_aff(t_core *ls, t_proc *proc, t_my_op *func)
{
	int par[1];

	par[0] = 0;
	printf("-s_exec cycle=%zu; pc=%zu; function_num=%d\n",ls->cycle, proc->pc, func->function_num);
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
	printf("-end_of_try_execute f_aff at cycle=%zu\n", ls->cycle);
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

void				write_data_block(t_core *ls, size_t data, size_t start, int len)
{
	int i;

	i = 0;
	if (len == 4)
		data = revert_32_bits_size_t(data);
	else if (len == 2)
		data = revert_16_bits_size_t(data);
	while (i < len && i < 5)
	{
		ls->field[((start + i) % MEM_SIZE)] = (data & 0xff);
		data = data >> OCTET;
		i++;
	}
}

size_t				read_data_block(t_core *ls, size_t start, int len)
{
	int i;
	size_t mem_block;

	mem_block = 0;
	i = 0;
	while (i < len && i < 9)
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
	ls->next_cycle_to_die = ls->cycle_to_die;

	(ls->players)[1] = (t_player *)ft_memalloc(sizeof(t_player));
	((ls->players)[1])->name = ft_strdup("second_player");
	(ls->players)[1]->comment = ft_strdup("very_unusefull comment");
	(ls->players)[1]->num = -2;
	ls->cycle_to_die = CYCLE_TO_DIE;
	ls->next_cycle_to_die = ls->cycle_to_die;

	int i = 0;

	while (i < ls->num_of_players)
	{
		add_proc_on_top(ls, (i * (MEM_SIZE / ls->num_of_players)), ((ls->players)[i])->num);
		i++;
	}
	// ls->processes_list = ft_memalloc(sizeof(t_proc));
	// ls->processes_list->reg[1] = 65;
	// ls->processes_list->ls = ls;
	ls->num_of_processes = ls->num_of_players;

	// add_proc_on_top(ls, MEM_SIZE/2, 255);
	// clone_proc(ls->processes_list->next, ls->processes_list);
}

void				opcode(t_core *ls, t_proc *proc)
{
	unsigned char opcode;

	if (proc->opcode_to_execute < 17 && proc->opcode_to_execute > 0)
	{
		((op_tab[(proc->opcode_to_execute)]).func)(ls, proc, &(op_tab[(proc->opcode_to_execute)]));
		// shift_pc(&(proc->pc), (op_tab[(proc->opcode_to_execute)]).cycles_to_exec);
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
		proc->execute_at = ls->cycle + (op_tab[opcode]).cycles_to_exec;
	}
	else
	{
		proc->execute_at = ls->cycle + 1;
		shift_pc(&(proc->pc), 1);
	}
}

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

	//par = 0;
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

void				add_proc_on_top(t_core *ls, int pc, int belong_to_player)
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
	size_t	last_live_of_winner;
	int		winner_num;

	winner_num = -1;
	last_live_of_winner = 0;
	i = 0;
	while(i < ls->num_of_players)
	{
		if (((ls->players)[i])->last_live >= last_live_of_winner) //не факт что больше равно
		{
			last_live_of_winner = ((ls->players)[i])->last_live;
			winner_num = i + 1;
		}
		i++;
	}//можно сделать указание что игрок выиграл не сказав лайв
	printf("GAME_ENDED\n");
	printf("The winner is: player %d, \"%s\"\n", winner_num, ((ls->players)[(winner_num - 1)])->name);
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

void				armageddon(t_core *ls)
{
	// if (ls->args->fl_dump && ls->cycle == ls->args->num_dump)
	// 	print_data(ls->field, MEM_SIZE, ls->args->width_dump);
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
		ls->gen_lives_in_current_period = 0;
		ls->next_cycle_to_die = ls->cycle + ls->cycle_to_die;
		ls->num_of_processes = kill_processes(&(ls->processes_list));
		if (!(ls->num_of_processes))
			game_end(ls);
	}
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
	print_data(tmp, code_len, 32);
	ft_strdel((char **)&tmp);
	print_data(ls->field, 64, 64);

	while (1)//ls->cycle < 25)//ls->cycle_to_die)
	{
		//if == ctd then check dead
		// printf("cycle=%06zu\n", ls->cycle);
		current_process =  ls->processes_list;
		armageddon(ls);
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
