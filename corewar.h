
#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

#include <errno.h>
#include "libft/libft.h"
#include "op.h"
#include "viz/viz.h"

typedef struct         s_op
{
	char             *name;
	int             args_nb;
	int             args[MAX_ARGS_NUMBER];
	int             binary;
	int             cycles;
	char            *descr;
	int             codage_oct;
	int             carry;
	int             label_size;
}                    t_op;

void		test(void);
int			ft_exit(char *str);
void		vm_init_struct(t_arg **ptr);
int			vm_valid(int argc, char **argv);
int			hndl_valid_file(char **argv, t_arg *ptr);
int			valid_filename(char **argv, t_arg *ptr);
void		sv_path_player(char *argv, t_arg *ptr);
int			find_ext_to_end(char *argv);
int			sv_number_player(char *argv, t_arg *ptr);
void		set_num_player(t_arg *ptr);
int			vm_valid_data_file(t_arg *ptr);
int			vm_init_struct_player(t_arg **ptr);


#endif
