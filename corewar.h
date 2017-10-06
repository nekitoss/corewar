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

struct				s_proc //processing
{
	size_t			pc;
	int				reg[REG_NUMBER + 1];
	char			carry;
	t_proc			*next;
}					t_proc;

struct				s_player
{
	char			*name;
	char			*comment;
	char			*program_code;
	size_t			last_live;
	unsigned int	sum_lives;
	int				num;
}					t_player;

struct				s_core
{
	size_t			cycle;
	size_t			gen_lives_in_current_period;
	size_t			cycle_to_die;
	t_player		**players;
	int				num_of_players;
	int				processes;
	int				cycles_per_second;
	char			paused;

}					s_core;


#endif
