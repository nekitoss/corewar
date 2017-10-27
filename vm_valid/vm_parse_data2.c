/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse_data2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:34:39 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/27 18:34:40 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	srch_dublicate_num_player(t_arg *ptr)
{
	int i;
	int j;

	i = 0;
	while (i < ptr->cnt_player)
	{
		if (ptr->num[i] > ptr->cnt_player || ptr->num[i] <= 0)
			ft_exit("Not correct number of player\n");
		j = i + 1;
		while (j < ptr->cnt_player)
		{
			if (ptr->num[i] == ptr->num[j])
				ft_exit("Error: dublicate number of player\n");
			j++;
		}
		i++;
	}


}

//
// Created by Maxim Kurchinskyj on 10/27/17.
//

