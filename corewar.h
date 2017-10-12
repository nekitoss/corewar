
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

int			ft_exit(char *str);
void		vm_init_struct(t_arg **ptr);
t_arg		*vm_valid(int argc, char **argv);
void		valid_filename(char **argv, t_arg *ptr);
void		sv_path_player(char *argv, t_arg *ptr, int *fl);
int			find_ext_to_end(char *argv);
void sv_number_player(char *argv, t_arg *ptr, int *fl);
void		set_num_player(t_arg *ptr);
int			vm_valid_data_file(t_arg *ptr);
int			vm_init_struct_player(t_arg **ptr);
int			vm_check_magic_byte(int fd);
int			vm_check_null(int fd);
void		vm_hndl_name(t_player *player, int fd);
void		vm_hndl_comment(t_player *player, int fd);
void		vm_hndl_size_code(t_player *player, int fd);

#endif
