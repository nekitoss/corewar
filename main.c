/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:38:31 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/27 20:38:34 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_exit(char *str)
{
	if (errno == 1)
		perror(str);
	else
		ft_putstr(str);
	exit(0);
}

void	ft_exit_name_file(t_player *player, char *str1, char *str2)
{
	ft_putstr(str1);
	ft_putstr(player->path_player);
	ft_putstr(str2);
	exit(0);
}

void	ft_save_number(t_arg *ptr)
{
	int i;

	i = 0;
	while (i < ptr->cnt_player)
	{
		ptr->player[i]->num *= -1;
		i++;
	}
}

void	vm_sort_player(t_arg *ptr)
{
	int			i;
	int			j;
	t_player	*tmp_player;

	i = 0;
	while (i < ptr->cnt_player)
	{
		j = i;
		while (j < ptr->cnt_player)
		{
			if (ptr->player[i]->num > ptr->player[j]->num)
			{
				tmp_player = ptr->player[i];
				ptr->player[i] = ptr->player[j];
				ptr->player[j] = tmp_player;
			}
			j++;
		}
		i++;
	}
	ft_save_number(ptr);
}

void	vm_show_usage(void)
{
	ft_putstr("Usage: ./corewar [-dump nbr_cycles [-w width]] [-debug [number]]"
		" [-m] [-v] [-o] [[-n number] champion1.cor] ...\n\n");
	ft_putstr("#### TEXT OUTPUT MODE ##########################################"
		"################\n");
	ft_putstr("-dump N      : Dumps memory after N cycles then exits\n");
	ft_putstr("-w N         : wide of dumps memory, in octets\n");
	ft_putstr("-m           : enable music\n");
	ft_putstr("-o           : make corewar like original\n");
	ft_putstr("-n N         : set number of player\n");
	ft_putstr("-debug N     : Verbosity levels, can be added together to enable"
		" several\n");
	ft_putstr("	- 0 : Show only essentials\n");
	ft_putstr("	- 1 : Show lives\n");
	ft_putstr("	- 2 : Show cycles\n");
	ft_putstr("	- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_putstr("	- 8 : Show deaths\n");
	ft_putstr("#### NCURSES OUTPUT MODE ###################################"
		"####################\n");
	ft_putstr("-v           : Ncurses output mode\n");
	ft_putstr("################################################################"
		"################\n");
	exit(0);
}
