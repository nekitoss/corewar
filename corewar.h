#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

#include "libft/libft.h"
#include "op.h"

typedef struct		s_op
{
	char			*name;
	int				args_nb;
	int				args[3];
	int				binary;
	int				cycles;
	char			*descr;
	int				codage_oct;
	int				carry;
	int				label_size;
}					t_op;

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
	t_player		**players;
	int				num_of_players;
	int				processes;
	int				cycles_per_second;
	char			paused;
	unsigned char	field[MEM_SIZE];
}					t_core;

#endif
