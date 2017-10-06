/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:46:25 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/02 14:46:26 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_init_struct(t_arg **ptr)
{
	(*ptr) = (t_arg*)malloc(sizeof(t_arg));
	(*ptr)->cnt_arg = -1;
	(*ptr)->nm_d = -1;
	(*ptr)->nm_n = -1;
	(*ptr)->nm_f = -1;
	(*ptr)->cnt_player = 0;
	(*ptr)->name_p1 = NULL;
	(*ptr)->name_p2 = NULL;
	(*ptr)->name_p3 = NULL;
	(*ptr)->name_p4 = NULL;
	(*ptr)->dump = -1;
	(*ptr)->n = -1;
	(*ptr)->num[0] = 0;
	(*ptr)->num[1] = 0;
	(*ptr)->num[2] = 0;
	(*ptr)->num[3] = 0;

}
