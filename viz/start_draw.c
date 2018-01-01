/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:51:47 by rhulam            #+#    #+#             */
/*   Updated: 2017/10/27 22:21:08 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"

void	draw_big(int y, int x, int x_s)
{
	int		i;

	i = 0;
	while (i < x)
		mvprintw(0, i++, "*");
	i = 0;
	while (i < x)
		mvprintw(y - 1, i++, "*");
	i = 0;
	while (i < y)
		mvprintw(i++, 0, "*");
	i = 0;
	while (i < y)
		mvprintw(i++, x - 1, "*");
	i = 0;
	while (i < y)
		mvprintw(i++, x_s - 1, "*");
}

void	draw_frame(void)
{
	start_color();
	use_default_colors();
	init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA);
	attron(COLOR_PAIR(1));
	draw_big(g_y, g_x_b, g_x_s);
	attroff(COLOR_PAIR(1));
}

void	initial_values(void)
{
	draw_frame();
	attron(A_BOLD);
	mvprintw(4, g_x_s + 2, "Cycles/second limit : ");
	mvprintw(7, g_x_s + 2, "Cycle : ");
	mvprintw(9, g_x_s + 2, "Processes : ");
	mvprintw(11, g_x_s + 2, "All lives : ");
	attroff(A_BOLD);
}

void	start_draw_2(t_core *core)
{
	attron(A_BOLD);
	mvprintw(g_pos + 2, g_x_s + 2, "Live breakdown for current period : ");
	mvprintw(g_pos + 5, g_x_s + 2, "Live breakdown for last period : ");
	attroff(A_BOLD);
	set_current_breakdown(0, 0, 0, 0);
	set_last_breakdown(0, 0, 0, 0);
	attron(A_BOLD);
	draw_constants();
	attroff(A_BOLD);
	init_color(COLOR_YELLOW, 510, 510, 510);
	init_pair(10, COLOR_WHITE, COLOR_GREEN);
	init_pair(11, COLOR_WHITE, COLOR_BLUE);
	init_pair(12, COLOR_WHITE, COLOR_RED);
	init_pair(13, COLOR_WHITE, COLOR_CYAN);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);
	draw_field(core);
	draw_carriage(core);
	refresh();
}

void	start_draw(t_core *core)
{
	t_arg *list;

	list = core->args;
	g_y = 68;
	g_x_s = 197;
	g_x_b = 264;
	g_m = core->args->fl_music;
	if (g_m)
	{
		signal(SIGINT, stop_and_exit);
		system("afplay song.mp3 &");
	}
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	nodelay(stdscr, true);
	n_pause();
	initial_values();
	set_cycles_per_second(0);
	set_cycle(0);
	set_processes(core->num_of_processes);
	set_all_lives(0);
	bots_draw(list);
	start_draw_2(core);
}
