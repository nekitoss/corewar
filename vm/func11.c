/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func11.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:44:26 by nekitoss          #+#    #+#             */
/*   Updated: 2017/10/27 21:44:27 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				empty_player_lives(t_core *ls)
{
	int i;

	i = 0;
	while (i < ls->num_of_players)
	{
		((ls->players)[i])->sum_lives_in_previous_period =
			((ls->players)[i])->sum_lives_in_current_period;
		((ls->players)[i])->sum_lives_in_current_period = 0;
		i++;
	}
	ls->gen_lives_in_previous_period = ls->gen_lives_in_current_period;
	ls->gen_lives_in_current_period = 0;
	ls->next_cycle_to_die = ls->cycle + ls->cycle_to_die;
	ls->num_of_processes = kill_processes(&(ls->processes_list), ls);
	if (!(ls->num_of_processes))
		game_end(ls);
}

void				debug_2_1(size_t a)
{
	ft_putstr("It is now cycle ");
	ft_putnbr(a);
	ft_putendl("");
}

void				debug_2_2(size_t a)
{
	ft_putstr("Cycle to die is now ");
	ft_putnbr(a);
	ft_putendl("");
}

void				armageddon(t_core *ls)
{
	if (ls->args->fl_dump && ls->cycle == ls->args->num_dump)
	{
		print_data(ls->field, MEM_SIZE, ls->args->width_dump);
		exit(0);
	}
	if (ls->cycle == ls->next_cycle_to_die)
	{
		if (ls->gen_lives_in_current_period >= NBR_LIVE ||
						ls->nbr_of_checks >= MAX_CHECKS - 1)
		{
			if (ls->cycle_to_die > CYCLE_DELTA)
			{
				ls->cycle_to_die -= CYCLE_DELTA;
				if (ls->args->num_debug & 2)
					debug_2_2(ls->cycle_to_die);
				ls->nbr_of_checks = 0;
			}
			else
				game_end(ls);
		}
		else
			(ls->nbr_of_checks)++;
		empty_player_lives(ls);
	}
}

void				preparate(t_core *ls, int argc, char **argv)
{
	if (argc == 1)
		vm_show_usage();
	ls->args = vm_valid(argc, argv);
	vm_sort_player(ls->args);
	ls->players = ls->args->player;
	init_my_player_and_process(ls);
	if (ls->args->fl_visual == 1)
		ls->args->num_debug = 0;
}
