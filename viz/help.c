/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:56:09 by rhulam            #+#    #+#             */
/*   Updated: 2017/10/27 18:10:11 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"

void	get_yx(int *yx, int pc)
{
	int					y;
	int					x;
	int					t;

	y = pc / 64;
	t = pc - 64 * y;
	if (!t)
	{
		yx[0] = y + 2;
		yx[1] = 3;
		return ;
	}
	x = t * 2 + t;
	yx[0] = y + 2;
	yx[1] = x + 3;
}

void	draw_cycle_2(t_core *core, int *arr, int *arr1)
{
	set_cycle_to_die(core->cycle_to_die);
	set_current_breakdown(arr[0], arr[1], arr[2], arr[3]);
	set_last_breakdown(arr1[0], arr1[1], arr1[2], arr1[3]);
}

void	draw_cycle(t_core *core)
{
	int					i;
	int					arr[4];
	int					arr1[4];

	i = 0;
	draw_field(core);
	draw_carriage(core);
	set_cycle(core->cycle);
	set_processes(core->num_of_processes);
	set_all_lives(core->gen_lives_in_current_period);
	while (i < core->num_of_players)
	{
		set_last_alive(i + 1, core->players[i]->last_live);
		set_live_in_current(i + 1,
				core->players[i]->sum_lives_in_current_period);
		arr[i] = core->players[i]->sum_lives_in_current_period;
		arr1[i] = core->players[i]->sum_lives_in_previous_period;
		i++;
	}
	while (i < 4)
	{
		arr[i] = 0;
		arr1[i++] = 0;
	}
	draw_cycle_2(core, arr, arr1);
}

void	draw_paused2(int c, unsigned int *cs)
{
	if (c == 119)
		*cs -= (*cs > 1) ? 1 : 0;
	else if (c == 113)
		*cs -= (*cs > 10) ? 10 : 0;
	else if (c == 101)
		*cs += (*cs < 2000) ? 1 : 0;
	else if (c == 114)
		*cs += (*cs < 1991) ? 10 : 0;
	else if (c == 116)
		*cs = 2000;
}

int		draw_paused(int *paused, t_core *core, unsigned int *cs)
{
	int					c;

	while (*paused)
	{
		set_cycles_per_second(*cs);
		c = getch();
		if (c == 32)
		{
			*paused = 0;
			n_run();
			draw_cycle(core);
			return (1);
		}
		else if (c == 115)
		{
			draw_cycle(core);
			return (1);
		}
		else
			draw_paused2(c, cs);
	}
	return (0);
}
