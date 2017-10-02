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

typedef struct		s_validation
{
	int				count_name;
	int				count_comment;
}					t_validation;

typedef	struct 		s_label
{
	char			*name;
	int 			byte;
	struct s_label	*next;
}					t_label;

typedef struct 		s_comands
{
	char 			*comand_name;
	char 			*label_name;
	int				codage;
	int 			size;
};

#endif