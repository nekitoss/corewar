#include "corewar.h"

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
	char			*program_code;
	size_t			last_live;
	unsigned int	sum_lives;
	int				num;
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

}					t_core;

t_my_op				op_tab[17] =
{
	{"live", 	1, {T_DIR},													1,	10,		"alive",								0, 0},
	{"ld", 		2, {T_DIR | T_IND, T_REG},									2,	5,		"load",									1, 0},
	{"st", 		2, {T_REG, T_IND | T_REG},									3,	5,		"store",								1, 0},
	{"add", 	3, {T_REG, T_REG, T_REG},									4,	10,		"addition",								1, 0},
	{"sub", 	3, {T_REG, T_REG, T_REG},									5,	10,		"soustraction",							1, 0},
	{"and", 	3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},	6,	6,		"et (and  r1, r2, r3   r1&r2 -> r3",	1, 0},
	{"or", 		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	7,	6,		"ou  (or   r1, r2, r3   r1 | r2 -> r3",	1, 0},
	{"xor", 	3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	8,	6,		"ou (xor  r1, r2, r3   r1^r2 -> r3",	1, 0},
	{"zjmp", 	1, {T_DIR},													9,	20,		"jump if zero",							0, 1},
	{"ldi", 	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			10,	25,		"load index",							1, 1},
	{"sti", 	3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			11,	25,		"store index",							1, 1},
	{"fork", 	1, {T_DIR},													12,	800,	"fork",									0, 1},
	{"lld", 	2, {T_DIR | T_IND, T_REG},									13,	10,		"long load",							1, 0},
	{"lldi", 	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			14,	50,		"long load index",						1, 1},
	{"lfork", 	1, {T_DIR},													15,	1000,	"long fork",							0, 1},
	{"aff", 	1, {T_REG},													16,	2,		"aff",									1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};


// size_t				hexstr_to_dec(char *str, int len)
// {
// 	while ()
// }

// void				read_data_block(t_core *ls, size_t start)
// {

// }


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
	t_core	*ls;

	ls = ft_memalloc(sizeof(t_core));
	init_my_player(ls);
	
	int fd = open("/nfs/2016/m/mpochuka/pool/corewar/src/test.cor", O_RDONLY);
	printf("offset=%lld\n", lseek(fd, 4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH + 4, SEEK_SET));
	char *tmp;
	get_next_line(fd, &tmp);
	printf("len=%zu=%s\n", ft_strlen(tmp), tmp);
	close(fd);

	unsigned int opcode;
	opcode = *tmp;
	printf("opcode = %d\n", opcode);
	tmp++;
	unsigned int coding_byte;
	coding_byte = *tmp;
	printf("%x\n", (coding_byte & 0b11000000));

	return (0);
}