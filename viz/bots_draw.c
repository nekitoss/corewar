/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bots_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 16:30:09 by rhulam            #+#    #+#             */
/*   Updated: 2017/10/27 16:30:31 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"

void	draw_bot(int i, char *name, int color)
{
	init_pair(i + 2, color, COLOR_BLACK);
	attron(COLOR_PAIR(i + 2));
	attron(A_BOLD);
	mvprintw(pos + 2, x_s + 2, "Player %d : %.50s", (i + 1) * -1, name);
	attroff(COLOR_PAIR(i + 2));
	mvprintw(pos + 3, x_s + 4, "Last live :                  ");
	mvprintw(pos + 4, x_s + 4, "Lives in current period :    ");
	attroff(A_BOLD);
	set_last_alive(i + 1, 0);
	set_live_in_current(i + 1, 0);
	pos += 4;
}

void	bots_draw(t_arg *list)
{
	int	i;

	i = 0;
	pos = 11;
	colors[0] = COLOR_GREEN;
	colors[1] = COLOR_BLUE;
	colors[2] = COLOR_RED;
	colors[3] = COLOR_CYAN;
	while (i < list->cnt_player)
	{
		draw_bot(i, list->player[i]->name, colors[i]);
		i++;
	}
}
