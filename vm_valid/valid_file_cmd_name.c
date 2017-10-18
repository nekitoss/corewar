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

#include <zconf.h>
#include "../corewar.h"

void	srch_num_player(int *num, t_arg *ptr)
{
	int i;
	int num_player;

	i = 0;
	num_player = 1;
	while (i < ptr->cnt_player)
	{
		if (ptr->num[i] == num_player)
		{
			num_player++;
			i = 0;
			continue;
		}
		i++;
	}

	*num = (num_player * -1);
}

void	set_num_player(t_arg *ptr)
{
	int i;

	i = 0;
	while (i < ptr->cnt_player)
	{
		if (ptr->num[i] == 0)
			srch_num_player(&(ptr->num[i]), ptr);
		i++;
	}
}

void	valid_filename(char **argv, t_arg *ptr)
{
	int i;
	int fl;

	fl = 0;
	i = 1;
	while (i < ptr->cnt_arg)
	{
		if (!ft_strcmp("-n", argv[i]))
			fl++;
		else if (!find_ext_to_end(argv[i]) && fl == 0)
			sv_path_player(argv[i], ptr, &fl);
		else if (!find_ext_to_end(argv[i]) && fl == 2)
			sv_path_player(argv[i], ptr, &fl);
		else if (fl == 1)
			sv_number_player(argv[i], ptr, &fl);
		else if (!ft_strcmp("-dump", argv[i]))
		{
			i += 2;
			continue;
		}
		else
			ft_exit("Error: in argument to line, think about this,"
							" my friend\n");
		i++;
	}
	if (fl != 0)
		ft_exit("Error: in argument to line, think about this,"
						" my friend)\n");
}

void		hndl_cmd_arg_wide(char **argv, t_arg *ptr, char *str)
{
	int i;
	long int num;

	i = 1;
	while (i < ptr->cnt_arg)
	{
		if (!ft_strcmp(str, argv[i]))
		{
			if (!valid_val_arg(argv[(i + 1)]))
			{
				ptr->fl_width = 1;
				if (ft_strlen(argv[(i + 1)]) > 10)
					ft_exit("Error: too big number, my friend\n");
				num = ft_atoi(argv[(i + 1)]);
				if (ft_strcmp(argv[(i + 1)], ft_itoa(num)))
					ft_exit("Error: to big number, my friend\n");
				ptr->width_dump = ft_atoi(argv[(i + 1)]);
			}
			else
				ft_exit("Error: incorrect val dump width, my friend\n");
		}
		i++;
	}
}