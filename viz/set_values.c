/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:26:00 by rhulam            #+#    #+#             */
/*   Updated: 2017/10/27 18:26:30 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"

void	set_cycles_per_second(int n)
{
	attron(A_BOLD);
	mvprintw(4, g_x_s + 2 + 22, "%d          ", n);
	attroff(A_BOLD);
	refresh();
}

void	set_cycle(size_t n)
{
	attron(A_BOLD);
	mvprintw(7, g_x_s + 2 + 8, "%d", n);
	attroff(A_BOLD);
	refresh();
}

void	set_processes(int n)
{
	attron(A_BOLD);
	mvprintw(9, g_x_s + 2 + 12, "%d           ", n);
	attroff(A_BOLD);
	refresh();
}

void	set_last_alive(int bot, size_t cycle)
{
	int		pos;

	pos = 14 + (4 * (bot - 1));
	attron(A_BOLD);
	mvprintw(pos, g_x_s + 4 + 29, "%d", cycle);
	attroff(A_BOLD);
	refresh();
}

void	set_live_in_current(int bot, int n)
{
	int		pos;

	pos = 15 + (4 * (bot - 1));
	attron(A_BOLD);
	mvprintw(pos, g_x_s + 4 + 29, "%d              ", n);
	attroff(A_BOLD);
	refresh();
}
