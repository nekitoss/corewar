#ifndef COREWAR_COREWAR_H
#define COREWAR_COREWAR_H

#include "libft/libft.h"
#include "op.h"
#include <errno.h>
#include <stdlib.h>

#define OCTET 8
#define TRUE 1
#define FALSE 0

#define P_PAR (proc->par)
#define P_REG (proc->reg)
#define P_COD_B (proc->coding_byte)
#define PROC_LIST (ls->processes_list)

typedef struct		s_player
{
	char			*name;
	char			*comment;
	unsigned char	*program_code;
	char			*path_player;
	size_t			last_live;
	unsigned int	sum_lives_in_current_period;
	unsigned int	sum_lives_in_previous_period;
	int				num;
	int				fd;
	int				size_code;
}					t_player;

typedef struct		s_arg
{
	int			cnt_arg;
	int			fl_dump;
	int			fl_debug;
	int			fl_visual;
	int			fl_width;
	int			fl_original;
	int			fl_music;
	size_t		num_dump;
	size_t		num_debug;
	int			width_dump;
	int			cnt_player;
	t_player	**player;
	char		*path_players[5];
	int			num[4];
}					t_arg;

typedef struct		s_proc
{
	size_t			pc;
	int				reg[REG_NUMBER + 1];
	unsigned char	is_alive;
	char			carry;
	size_t			execute_at;
	unsigned char	opcode_to_execute;
	size_t			alive_at;
	char			belong_to_player;
	unsigned char	coding_byte;
	size_t			old_pc;
	int				par[3];
	size_t			number;
	struct s_core	*ls;
	struct s_proc	*next;
}					t_proc;



typedef struct		s_core
{
	size_t			cycle;
	size_t			gen_lives_in_current_period;
	size_t			gen_lives_in_previous_period;
	size_t			cycle_to_die;
	size_t			next_cycle_to_die;
	size_t			nbr_of_checks;
	t_player		**players;
	int				num_of_players;
	int				num_of_processes;
	unsigned char	field[MEM_SIZE];
	char			colors[MEM_SIZE];
	size_t			pr_cnt;
	t_proc			*processes_list;
	t_arg			*args;
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
}					g_my_op;



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

void				f_live(t_core *ls, t_proc *proc, g_my_op *func);
void				f_ld(t_core *ls, t_proc *proc, g_my_op *func);
void				f_st(t_core *ls, t_proc *proc, g_my_op *func);
void				f_add(t_core *ls, t_proc *proc, g_my_op *func);
void				f_sub(t_core *ls, t_proc *proc, g_my_op *func);
void				f_and(t_core *ls, t_proc *proc, g_my_op *func);
void				f_or(t_core *ls, t_proc *proc, g_my_op *func);
void				f_xor(t_core *ls, t_proc *proc, g_my_op *func);
void				f_zjmp(t_core *ls, t_proc *proc, g_my_op *func);
void				f_ldi(t_core *ls, t_proc *proc, g_my_op *func);
void				f_sti(t_core *ls, t_proc *proc, g_my_op *func);
void				f_fork(t_core *ls, t_proc *proc, g_my_op *func);
void				f_lld(t_core *ls, t_proc *proc, g_my_op *func);
void				f_lldi(t_core *ls, t_proc *proc, g_my_op *func);
void				f_lfork(t_core *ls, t_proc *proc, g_my_op *func);
void				f_aff(t_core *ls, t_proc *proc, g_my_op *func);



#if VIZU
#include "viz/viz.h"
#endif

int			ft_exit(char *str);
void		vm_init_struct(t_arg **ptr);
t_arg		*vm_valid(int argc, char **argv);
void		valid_filename(char **argv, t_arg *ptr);
void		sv_path_player(char *argv, t_arg *ptr, int *fl);
int			find_ext_to_end(char *argv);
void		sv_number_player(char *argv, t_arg *ptr, int *fl);
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
int			valid_val_arg(char *argv, char **cur);
// int ft_exit(char *str)
// void 	ft_exit_name_file(t_player *player, char *str1, char *str2)
void		for_test(t_arg *ptr);
void		vm_sort_player(t_arg *ptr);
void		vm_show_usage(void);
void		valid_flags(t_arg *ptr);
void		ft_save_val_width(t_arg *ptr, char **argv, int i, char **cur);
int			hndl_cmd_arg_debug(char **argv, t_arg *ptr, char *str);
void		hndl_cmd_arg_music(char **argv, t_arg *ptr, char *str);
void		hndl_cmd_arg_original(char **argv, t_arg *ptr, char *str);


void				convert_param_to_data(t_proc *proc, int par_num);
void				convert_param_to_data_no_idx(t_proc *proc, int par_num);
unsigned char		ident_param(unsigned char coding_byte, int param_num);
int					calculate_pc_shift(g_my_op *func, unsigned char coding_byte, int par_num);
int					read_non_conv_parameters_and_shift(g_my_op *func, t_proc *proc);
short				revert_16_bits_size_t(short num);
int					revert_32_bits_size_t(int num);
void				write_data_block(t_proc *proc, int data, unsigned int start, int len);
char				read_1_byte(t_core *ls, unsigned int start);
short				read_2_byte(t_core *ls, unsigned int start);
int					read_4_byte(t_core *ls, unsigned int start);
int					read_data_block(t_core *ls, unsigned int start, int len);
void				print_data(unsigned char *str, size_t len, size_t width);
void				shift_pc(size_t *pc, unsigned int value);
void				set_next_ex(size_t *next_execution_at, int value);
void				set_initial_code_color(char *colors, int pl_num, int len);
void				init_my_player_and_process(t_core *ls);
void				opcode(t_core *ls, t_proc *proc);
int					cmp_one_param(g_my_op *func, unsigned char coding_byte, int param_num);
void				add_proc_on_top(t_core *ls, unsigned int pc, int belong_to_player);
void				clone_proc(t_proc *father, t_proc *son);
void				game_end(t_core *ls);
int					calculate_processes_and_0lives(t_proc *proc);
int					kill_processes(t_proc **head, t_core *ls);
void				empty_player_lives(t_core *ls);
void				armageddon(t_core *ls);
#endif
