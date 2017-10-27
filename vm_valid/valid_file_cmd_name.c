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

void	valid_flags(t_arg *ptr)
{
	if (ptr->fl_dump == 0 && ptr->fl_width == 1)
		ft_exit("Error: flag width cannot use without flag dump\n");
	if (ptr->cnt_player == 0)
		vm_show_usage();
}

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
	*num = num_player;
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
		if ((ft_parse_cmd_line(ptr, argv, &fl, &i)) == 3)
			continue;
		i++;
	}
	if (fl != 0)
		ft_exit("Error: invalid argument in cmd line,think about this,"
			"my friend\n");
}

void	hndl_cmd_arg_wide(char **argv, t_arg *ptr, char *str)
{
	int		i;
	char	*cur;

	i = 1;
	while (i < ptr->cnt_arg)
	{
		if (!ft_strcmp(str, argv[i]))
		{
			if (i + 1 >= ptr->cnt_arg)
				ft_exit("Error: incorrect value of width dump\n");
			if (!valid_val_arg(argv[(i + 1)], &cur))
				ft_save_val_width(ptr, argv, i, &cur);
			else
				ft_exit("Error: incorrect value of dump width, my friend\n");
		}
		i++;
	}
}
