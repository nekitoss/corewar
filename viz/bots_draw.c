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
	mvprintw(g_pos + 2, g_x_s + 2, "Player %d : %.50s", (i + 1) * -1, name);
	attroff(COLOR_PAIR(i + 2));
	mvprintw(g_pos + 3, g_x_s + 4, "Last live :                  ");
	mvprintw(g_pos + 4, g_x_s + 4, "Lives in current period :    ");
	attroff(A_BOLD);
	set_last_alive(i + 1, 0);
	set_live_in_current(i + 1, 0);
	g_pos += 4;
}

void	bots_draw(t_arg *list)
{
	int	i;

	i = 0;
	g_pos = 11;
	g_colors[0] = COLOR_GREEN;
	g_colors[1] = COLOR_BLUE;
	g_colors[2] = COLOR_RED;
	g_colors[3] = COLOR_CYAN;
	while (i < list->cnt_player)
	{
		draw_bot(i, list->player[i]->name, g_colors[i]);
		i++;
	}
}

void	drawing_4(int *first)
{
	*first = 0;
}

void	draw_field(t_core *core)
{
	int					x;
	int					y;
	int					i;
	int					t;

	x = 3;
	y = 2;
	i = 0;
	while (i < MEM_SIZE)
	{
		t = (int)(core->colors[i]) ? (int)(core->colors[i]) * -1 : 6;
		attron(COLOR_PAIR(t + 1));
		mvprintw(y, x, "%.2x", core->field[i]);
		attroff(COLOR_PAIR(t + 1));
		x += 3;
		if (x >= 195)
		{
			x = 3;
			y++;
		}
		i++;
	}
	refresh();
}

void	draw_carriage(t_core *core)
{
	t_proc				*temp;
	int					yx[2];

	temp = core->processes_list;
	while (temp)
	{
		get_yx(yx, temp->pc);
		attron(COLOR_PAIR(temp->belong_to_player * -1 + 9));
		mvprintw(yx[0], yx[1], "%.2x", core->field[temp->pc]);
		attroff(COLOR_PAIR(temp->belong_to_player * -1 + 9));
		refresh();
		temp = temp->next;
	}
}
