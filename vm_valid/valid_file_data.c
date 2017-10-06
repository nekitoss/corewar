/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:10:00 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/03 14:10:03 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		srch_num_player(int *num, t_arg *ptr)
{
	int i;
	int num_player;

	i = 0;
	num_player = 1;
	while (i < 5)
	{
		if (ptr->num[i] == num_player)
		{
			num_player++;
			i = 0;
			continue;
		}
		i++;
	}

	*num = num_player;
}

void		set_num_player(t_arg *ptr)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (ptr->num[i] == 0)
			srch_num_player(&(ptr->num[i]), ptr);
		i++;
	}
}

int		valid_filename(char **argv, t_arg *ptr)
{
	int i;
	int fl;

	fl = 0;
	i = (ptr->dump == 1) ? 2 : 1;
	while (argv[i] != 0)
	{
		if (!ft_strcmp("-n", argv[i]))
			fl++;
		else if (argv[i][0] != '.' && !find_ext_to_end(argv[i]) && fl == 0)
		{
			sv_path_player(argv[i], ptr);
			fl = 0;
		}
		else if (argv[i][0] != '.' && !find_ext_to_end(argv[i]) && fl == 2)
		{
			sv_path_player(argv[i], ptr);
			fl = 0;
		}
		else if (fl == 1)
		{
			if (sv_number_player(argv[i], ptr))
				return (1);
			fl++;
		}
		else
			return (1);
		i++;
	}
	return (0);
}
