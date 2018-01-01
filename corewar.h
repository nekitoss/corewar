/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 22:26:02 by nekitoss          #+#    #+#             */
/*   Updated: 2017/10/27 22:26:05 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_COREWAR_H
# define COREWAR_COREWAR_H

# include "struct.h"
# include <errno.h>
# include <stdlib.h>
# include "viz/viz.h"

# define OCTET 8
# define TRUE 1
# define FALSE 0

# define P_PAR (proc->par)
# define P_REG (proc->reg)
# define P_COD_B (proc->coding_byte)
# define PROC_LIST (ls->processes_list)

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
int					ft_exit(char *str);
void				vm_init_struct(t_arg **ptr);
t_arg				*vm_valid(int argc, char **argv);
void				valid_filename(char **argv, t_arg *ptr);
void				sv_path_player(char *argv, t_arg *ptr, int *fl);
int					find_ext_to_end(char *argv);
void				sv_number_player(char *argv, t_arg *ptr, int *fl);
void				set_num_player(t_arg *ptr);
int					vm_valid_data_file(t_arg *ptr);
int					vm_init_struct_player(t_arg **ptr);
void				vm_check_magic_byte(int fd);
void				vm_check_null(int fd, int num);
void				vm_hndl_name(t_player *player, int fd);
void				vm_hndl_comment(t_player *player, int fd);
void				vm_hndl_size_code(t_player *player, int fd);
void				vm_hndl_code(t_player *player, int fd);
void				ft_exit_name_file(t_player *player, char *str1, char *str2);
void				ft_exit_size_code(t_player *player, char *str1,
	char *str2, char *str3);
void				hndl_cmd_arg_visual(char **argv, t_arg *ptr, char *str);
void				hndl_cmd_arg_wide(char **argv, t_arg *ptr, char *str);
int					valid_val_arg(char *argv, char **cur);
void				vm_sort_player(t_arg *ptr);
void				vm_show_usage(void);
void				valid_flags(t_arg *ptr);
void				ft_save_val_width(t_arg *ptr, char **argv,
	int i, char **cur);
int					hndl_cmd_arg_debug(char **argv, t_arg *ptr, char *str);
void				hndl_cmd_arg_music(char **argv, t_arg *ptr, char *str);
void				hndl_cmd_arg_original(char **argv, t_arg *ptr, char *str);
int					ft_parse_cmd_line(t_arg *ptr, char **argv, int *fl, int *i);
void				hndl_cmd_arg_n(char **argv, t_arg *ptr);
void				srch_dublicate_num_player(t_arg *ptr);
void				convert_param_to_data(t_proc *proc, int par_num);
void				convert_param_to_data_no_idx(t_proc *proc, int par_num);
unsigned char		ident_param(unsigned char coding_byte, int param_num);
int					calculate_pc_shift(t_my_op *func, unsigned char coding_byte,
	int par_num);
int					read_non_conv_parameters_and_shift(t_my_op *func,
	t_proc *proc);
short				revert_16_bits_size_t(short num);
int					revert_32_bits_size_t(int num);
void				write_data_block(t_proc *proc, int data,
	unsigned int start, int len);
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
int					cmp_one_param(t_my_op *func,
	unsigned char coding_byte, int param_num);
void				add_proc_on_top(t_core *ls,
	unsigned int pc, int belong_to_player);
void				clone_proc(t_proc *father, t_proc *son);
void				game_end(t_core *ls);
int					calculate_processes_and_0lives(t_proc *proc);
int					kill_processes(t_proc **head, t_core *ls);
void				empty_player_lives(t_core *ls);
void				armageddon(t_core *ls);
void				hex_print(unsigned char val);
void				print_winner(t_core *ls, int winner_num);
void				free_players(t_core *ls);
void				free_proc(t_proc *pr);
void				free_core(t_core *ls);
void				debug_8(t_core *ls, size_t a, size_t b, size_t c);
void				debug_2_1(size_t a);
void				debug_2_2(size_t a);
void				preparate(t_core *ls, int argc, char **argv);
void				debug_4(t_proc *proc, t_my_op *func, int r);
#endif
