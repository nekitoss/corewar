/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 16:54:40 by yrobotko          #+#    #+#             */
/*   Updated: 2017/09/22 16:54:57 by yrobotko         ###   ########.fr       */
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

typedef	struct 			s_label
{
	char				*name;
	int 				byte_num;
	struct s_label		*next;
}						t_label;

typedef struct 			s_commands
{
	char	 			*command_name;
	char	 			**labels;
	char 				*P;
	int	 				*param;
	int					codage;
	int 				size;
	struct s_commands	*next;
}						t_commands;

typedef	struct 			s_asm
{
	t_label				*labels;
	t_commands			*commands;
	struct header_s		*head;
	int 				count_byte;
}						t_asm;

int 	check_label_or_comm(char *s);
#endif