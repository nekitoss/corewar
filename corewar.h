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

// typedef struct		s_proc
// {
// 	size_t			pc;
// 	int				reg[REG_NUMBER + 1];
// 	char			carry;
// 	struct s_proc	*next;
// }					t_proc;

// typedef struct		s_player
// {
// 	char			*name;
// 	char			*comment;
// 	unsigned char	*program_code;
// 	size_t			last_live;
// 	unsigned int	sum_lives;
// 	int				num;
// 	int				code_size;
// }					t_player;

// typedef struct		s_core
// {
// 	size_t			cycle;
// 	size_t			gen_lives_in_current_period;
// 	size_t			cycle_to_die;
// 	t_player		**players;
// 	int				num_of_players;
// 	int				processes;
// 	int				cycles_per_second;
// 	char			paused;
// 	unsigned char	field[MEM_SIZE];
// }					t_core;

// t_


#include <errno.h>
// #include "viz/viz.h"

// typedef struct         s_op
// {
// 	char             *name;
// 	int             args_nb;
// 	int             args[MAX_ARGS_NUMBER];
// 	int             binary;
// 	int             cycles;
// 	char            *descr;
// 	int             codage_oct;
// 	int             carry;
// 	int             label_size;
// }                    t_op;

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
void		vm_check_magic_byte(int fd);
void		vm_check_null(int fd, int num);
void		vm_hndl_name(t_player *player, int fd);
void		vm_hndl_comment(t_player *player, int fd);
void		vm_hndl_size_code(t_player *player, int fd);
void		vm_hndl_code(t_player *player, int fd);
void		ft_exit_name_file(t_player *player, char *str1, char *str2);
void		ft_exit_size_code(t_player *player, char *str1, char *str2, char *str3);
void		hndl_cmd_arg_visual(char **argv, t_arg *ptr, char *str);
void		hndl_cmd_arg_wide(char **argv, t_arg *ptr, char *str);
int			valid_val_arg(char *argv);
// int ft_exit(char *str)
// void 	ft_exit_name_file(t_player *player, char *str1, char *str2)
void		for_test(t_arg *ptr);
void		vm_sort_player(t_arg *ptr);
void		vm_show_usage(void);

#endif
