/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 16:54:40 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/23 18:39:35 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct			s_validation
{
	int					count_name;
	int					count_comment;
}						t_validation;

typedef	struct			s_label
{
	char				*name;
	int					byte_num;
	struct s_label		*next;
}						t_label;

typedef struct			s_commands
{
	char				*command_name;
	char				**labels;
	char				*p;
	int					*param;
	int					codage;
	int					size;
	struct s_commands	*next;
}						t_commands;

typedef	struct			s_asm
{
	t_label				*labels;
	t_commands			*commands;
	struct s_header		*head;
	int					count_byte;
}						t_asm;

int						check_label_or_comm(char *s);
void					error(char *str);
t_label					*new_labels();
t_commands				*new_commands();
t_asm					*new_struct();
t_validation			*new_valid();
int						check_file_name(char *s);
char					*read_file(int fd);
unsigned int			reverse_bit(unsigned int a);
t_header				*new_head();
char					*get_name(char *str);
void					check_quotes(char *str, int i);
char					*check_name(char *str);
void					cpy(char **dest, char *str);
char					*check_comment(char *str);
void					valid_head(t_header *head, char **str);
void					del_com(char **s);
int						ft_stcmp(char *s1, char *s2);
int						is_command(char *s);
int						is_label(char *s);
char					*get_lb_name(char *s);
int						check_repeat(t_label *lb, char *s);
int						add_label(t_asm *masm, char *s);
void					pass_spaces(char **s);
void					check_separator(char *s, int index);
void					check_lb_char(char **s);
void					check_dir(char **s);
void					check_reg(char **s);
void					check_indir(char **s);
void					check_num(char **s);
void					check_parameter(char **s);
void					check_args(char *s, int index);
t_commands				*get_empty_struc(t_commands *c);
int						check_type(char **s, int ind, int index);
void					goto_next_param(char **s);
int						add_reg(t_commands *comm, int i, char **s);
int						add_indir(t_commands *comm, int i, char **s);
int						add_lbdir(t_commands *comm, int i, int ind, char **s);
int						add_dir(t_commands *comm, int i, int ind, char **s);
int						set_param(t_commands *comm, int i, int index, char **s);
void					add_to_struct(t_asm *masm, int ind, char **s);
void					check_command(t_asm *masm, char **str);
int						check_label(t_asm *masm, char **str);
int						is_empty(char *s);
int						pass_it(char *s);
void					valid_code(t_asm *masm, char *str, t_header *head);
char					*make_name(char *s);
int						get_ind(char *s);
int						get_codege(char *p, int i);
void					write_codage(int fdwrite, t_commands *comm);
unsigned int			reverse_two_bit(unsigned int a);
void					write_reg(int fd, int param);
int						get_length(int curr_byte, int lb_byte, int fl);
void					write_indir(int fd, t_commands *comm, t_label *lb,
		int i);
void					write_dir(int fd, t_commands *comm, t_label *lb, int i);
void					write_param(int fd, t_commands *comm, t_label *lb,
		int i);
void					write_to_cor(int fdwrite, t_commands *comm,
		t_label *lb);
void					make_corfile(t_asm *masm, t_commands *comm,
		t_label	*lb, char *name);
int						find_lb(char *s, t_label *lb);
void					check_lb(t_commands *comm, t_label	*lb);
long long				fft_atoi(const char *str);
void					free_lb(t_label *lb);
void					free_comm(t_commands *comm);
void					free_main(t_asm *mstruc);
int						ft_stcmp1(char *s1, char *s2);
int						is_command1(char *s);
int						label_or_comm(char *s);
int						no_quote(char *s);
void					skip_it(char **s);
char					*check_name_alfa(char *str);
char					*check_comment_alfa(char *str);
void					del_only_comments(char *s, char	*name, char *comment);

#endif
