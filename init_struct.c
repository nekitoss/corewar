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

void	vm_init_struct(t_arg **ptr)
{
	(*ptr) = (t_arg*)malloc(sizeof(t_arg));
	(*ptr)->cnt_arg = -1;
	(*ptr)->fl_dump = -1;
	(*ptr)->num_dump = -1;
	(*ptr)->pos_dump = -1;
	(*ptr)->visual = 0;
	(*ptr)->cnt_player = 0;
	(*ptr)->path_players[0] = NULL;
	(*ptr)->path_players[1] = NULL;
	(*ptr)->path_players[2] = NULL;
	(*ptr)->path_players[3] = NULL;
	(*ptr)->path_players[4] = NULL;
	(*ptr)->player = NULL;
	(*ptr)->num_dump = -1;
	(*ptr)->n = -1;
	(*ptr)->num[0] = 0;
	(*ptr)->num[1] = 0;
	(*ptr)->num[2] = 0;
	(*ptr)->num[3] = 0;

}

int 	vm_init_struct_player(t_arg **ptr)
{
	int i;
	
	i = 0;

	(*ptr)->player = (t_player**)malloc(sizeof(t_player*) * 4);
	if ((*ptr)->player == NULL)
		ft_exit("Could not allocation memory");
	while (i < (*ptr)->cnt_player)
	{
		(*ptr)->player[i] = (t_player*)malloc(sizeof(t_player));
		if ((*ptr)->player[i] == NULL)
			ft_exit("Could not allocation memory");
		(*ptr)->player[i]->name = NULL;
		(*ptr)->player[i]->comment = NULL;
		(*ptr)->player[i]->program_code = NULL;
		(*ptr)->player[i]->last_live = 0;
		(*ptr)->player[i]->sum_lives = 0;
		(*ptr)->player[i]->num = 0;
		(*ptr)->player[i]->fd = 0;
		(*ptr)->player[i]->size_code = 0;
		i++;
	}
	return (0);
}
