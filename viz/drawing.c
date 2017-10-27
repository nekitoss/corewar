/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 16:31:30 by rhulam            #+#    #+#             */
/*   Updated: 2017/10/27 17:52:12 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"

void	drawing_2(int c, unsigned int *cs)
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

void	drawing_3(t_core *core, int *paused)
{
	draw_cycle(core);
	n_pause();
	*paused = 1;
}

void	drawing_5(t_core *core, unsigned int cs)
{
	set_cycles_per_second(cs);
	draw_cycle(core);
	usleep(1000000 / cs);
}

int		drawing_6(int *paused, t_core *core, unsigned int *cs)
{
	*paused = 1;
	n_pause();
	if (draw_paused(paused, core, cs))
		return (1);
	return (0);
}

void	drawing(t_core *core)
{
	int					c;
	static unsigned int	cs = 50;
	static int			paused = 1;
	static int			first = 1;
	static unsigned int	counter;

	if (++counter < cs / 30 && !paused)
		return ;
	counter = 0;
	if (first)
		return (drawing_4(&first));
	if (paused)
		if (draw_paused(&paused, core, &cs))
			return ;
	c = getch();
	if (c == 32)
	{
		if (drawing_6(&paused, core, &cs))
			return ;
	}
	else if (c == 115)
		return (drawing_3(core, &paused));
	else
		drawing_2(c, &cs);
	drawing_5(core, cs);
}
