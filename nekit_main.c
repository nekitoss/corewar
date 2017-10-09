#include "corewar.h"

#define OCTET 8

typedef struct		s_proc
{
	size_t			pc;
	int				reg[REG_NUMBER + 1];
	char			carry;
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
	int				processes;
	int				cycles_per_second;
	char			paused;
	unsigned char	field[MEM_SIZE];
}					t_core;

// t_my_op				op_tab[17] =
// {
// 	{"live", 	1, {T_DIR},													1,	10,		"alive",								0, 0},
// 	{"ld", 		2, {T_DIR | T_IND, T_REG},									2,	5,		"load",									1, 0},
// 	{"st", 		2, {T_REG, T_IND | T_REG},									3,	5,		"store",								1, 0},
// 	{"add", 	3, {T_REG, T_REG, T_REG},									4,	10,		"addition",								1, 0},
// 	{"sub", 	3, {T_REG, T_REG, T_REG},									5,	10,		"soustraction",							1, 0},
// 	{"and", 	3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},	6,	6,		"et (and  r1, r2, r3   r1&r2 -> r3",	1, 0},
// 	{"or", 		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	7,	6,		"ou  (or   r1, r2, r3   r1 | r2 -> r3",	1, 0},
// 	{"xor", 	3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	8,	6,		"ou (xor  r1, r2, r3   r1^r2 -> r3",	1, 0},
// 	{"zjmp", 	1, {T_DIR},													9,	20,		"jump if zero",							0, 1},
// 	{"ldi", 	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			10,	25,		"load index",							1, 1},
// 	{"sti", 	3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			11,	25,		"store index",							1, 1},
// 	{"fork", 	1, {T_DIR},													12,	800,	"fork",									0, 1},
// 	{"lld", 	2, {T_DIR | T_IND, T_REG},									13,	10,		"long load",							1, 0},
// 	{"lldi", 	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			14,	50,		"long load index",						1, 1},
// 	{"lfork", 	1, {T_DIR},													15,	1000,	"long fork",							0, 1},
// 	{"aff", 	1, {T_REG},													16,	2,		"aff",									1, 0},
// 	{0, 0, {0}, 0, 0, 0, 0, 0}
// };


// size_t				hexstr_to_dec(char *str, int len)
// {
// 	while ()
// }

size_t				revert_16_bits_size_t(size_t num);
size_t				revert_32_bits_size_t(size_t num);

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

void				revert_16_bits(unsigned short int *num)
{
	*num = ((*num) >> 8) | ((*num) << 8);
	return ;
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

void				revert_32_bits(unsigned int *num)
{
	*num = (((*num) >> 24) & 0xff) | // move byte 3 to byte 0
                    (((*num) << 8) & 0xff0000) | // move byte 1 to byte 2
                    (((*num) >> 8) & 0xff00) | // move byte 2 to byte 1
                    (((*num) << 24) & 0xff000000); // byte 0 to byte 3
	return ;
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
	printf("counter = %4zu\n", *pc);
}				

void				init_my_player(t_core *ls)
{
	ls->num_of_players = 1;
	ls->players = (t_player **)ft_memalloc(sizeof(t_player *) * ls->num_of_players);
	(ls->players)[0] = (t_player *)ft_memalloc(sizeof(t_player));
	((ls->players)[0])->name = ft_strdup("my_name");
	(ls->players)[0]->comment = ft_strdup("some_unusefull comment");
	(ls->players)[0]->num = -1;
}

int					main(void)
{
	size_t prog_counter = 0;
	t_core	*ls;

	ls = ft_memalloc(sizeof(t_core));
	init_my_player(ls);
	
	int fd = open("/nfs/2016/m/mpochuka/pool/corewar/src/test.cor", O_RDONLY);
	size_t file_size = lseek(fd, 0, SEEK_END);
	size_t offset = lseek(fd, 4 + PROG_NAME_LENGTH + 1 + 3 + sizeof(int) + COMMENT_LENGTH + 1 + 3, 0);
	
	unsigned char *tmp;
	size_t code_len = file_size - offset;
	tmp = (unsigned char *)ft_strnew(code_len);
	read (fd, tmp, code_len);
	printf("file_size=%zu; offset=%zu; len=%zu\n", file_size, offset, code_len);
	close(fd);

	ft_memcpy((void **)&((ls->field)[prog_counter]), tmp, code_len);
	print_data(tmp, code_len);
	ft_strdel((char **)&tmp);
	print_data(ls->field, 32);
	
	unsigned int opcode;
	opcode = read_data_block(ls, prog_counter, 1);
	printf("opcode = %d\n", opcode);
	shift_pc(&prog_counter, 1);

	unsigned char coding_byte;
	coding_byte = read_data_block(ls, prog_counter, 1);
	printf("coding byte_int=%u, codingbyte_hex=%#x\n", coding_byte, (coding_byte));// & 0b11000000));
	shift_pc(&prog_counter, 1);
	
	unsigned int par1;

	par1 = read_data_block(ls, prog_counter, 4);
	shift_pc(&prog_counter, 4);
	printf("par1_hex=%#x; %u\n", par1, par1%MEM_SIZE);

	unsigned int par2;

	par2 = read_data_block(ls, prog_counter, 1);
	shift_pc(&prog_counter, 1);
	printf("par2_hex=%#x; %u\n", par2, par2%MEM_SIZE);


	return (0);
}