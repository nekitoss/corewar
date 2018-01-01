/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:21:54 by rhulam            #+#    #+#             */
/*   Updated: 2017/10/27 22:20:02 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"

void	n_run(void)
{
	attron(A_BOLD);
	move(2, g_x_s + 2);
	printw("** RUNNING **");
	refresh();
	attroff(A_BOLD);
}

void	n_pause(void)
{
	attron(A_BOLD);
	move(2, g_x_s + 2);
	printw("** PAUSE **  ");
	refresh();
	attroff(A_BOLD);
}

void	stop_and_exit(int signal)
{
	if (g_m)
	{
		if (signal != 2 && signal != -100)
			return ;
		system("killall afplay");
		endwin();
		if (signal != -100)
			exit(-1);
	}
	endwin();
}

void	end_draw(t_player *player)
{
	attron(A_BOLD);
	attron(COLOR_PAIR(player->num * -1 + 1));
	if (ft_strlen(player->name) > 34)
		mvprintw(64, g_x_s + 2, "The winner is: player %d, \"%.32s...",
				player->num, player->name);
	else
		mvprintw(64, g_x_s + 2, "The winner is: player %d, \"%.34s\"",
				player->num, player->name);
	attroff(COLOR_PAIR(player->num * -1 + 1));
	mvprintw(65, g_x_s + 2, "Press any key to exit");
	attroff(A_BOLD);
	nodelay(stdscr, false);
	getch();
	stop_and_exit(-100);
}
