/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:13:08 by rhulam            #+#    #+#             */
/*   Updated: 2017/10/27 18:14:06 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"

void	draw_constants(void)
{
	mvprintw(g_pos + 8, g_x_s + 2, "CYCLE_TO_DIE : %d", CYCLE_TO_DIE);
	mvprintw(g_pos + 10, g_x_s + 2, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvprintw(g_pos + 12, g_x_s + 2, "NBR_LIVE : %d", NBR_LIVE);
	mvprintw(g_pos + 14, g_x_s + 2, "MAX_CHECKS : %d", MAX_CHECKS);
}

void	set_all_lives(size_t n)
{
	attron(A_BOLD);
	mvprintw(11, g_x_s + 2 + 12, "%d            ", n);
	attroff(A_BOLD);
	refresh();
}

void	set_cycle_to_die(size_t n)
{
	attron(A_BOLD);
	mvprintw(g_pos + 8, g_x_s + 2 + 15, "%d               ", n);
	attroff(A_BOLD);
	refresh();
}

void	set_last_breakdown_3(int fourth, int *i)
{
	while (fourth)
	{
		attron(COLOR_PAIR(5));
		mvprintw(g_pos + 6, g_x_s + 2 + (*i)++, "-");
		attroff(COLOR_PAIR(5));
		fourth--;
	}
}
