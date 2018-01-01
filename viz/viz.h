/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 19:01:22 by rhulam            #+#    #+#             */
/*   Updated: 2017/10/27 19:04:04 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSES_VIZ_H
# define NCURSES_VIZ_H

# include <curses.h>
# include "../corewar.h"
# include <signal.h>

int g_y;
int g_x_s;
int g_x_b;
int g_colors[4];
int g_pos;
int g_m;

void	start_draw(t_core *list);
void	n_run(void);
void	n_pause(void);
void	set_cycles_per_second(int n);
void	set_cycle(size_t n);
void	set_processes(int n);
void	bots_draw(t_arg *list);
void	set_last_alive(int bot, size_t cycle);
void	set_live_in_current(int bot, int n);
void	set_current_breakdown(int a, int b, int c, int d);
void	set_last_breakdown(double a, double b, double c, double d);
void	draw_constants(void);
void	set_cycle_to_die(size_t n);
void	end_draw(t_player *player);
void	set_all_lives(size_t n);
void	drawing(t_core *core);
void	draw_carriage(t_core *core);
void	draw_field(t_core *core);
void	stop_and_exit(int signal);
int		draw_paused(int *paused, t_core *core, unsigned int *cs);
void	draw_cycle(t_core *core);
void	drawing_4(int *first);
void	get_yx(int *yx, int pc);
void	set_last_breakdown_3(int fourth, int *i);

#endif
