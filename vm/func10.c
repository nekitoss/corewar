/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:43:31 by nekitoss          #+#    #+#             */
/*   Updated: 2017/10/27 21:43:31 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void				game_end(t_core *ls)
{
	int		i;
	ssize_t	last_live_of_winner;
	int		winner_num;

	winner_num = -1;
	last_live_of_winner = -1;
	i = 0;
	while (i < ls->num_of_players)
	{
		if ((ssize_t)(((ls->players)[i])->last_live) > last_live_of_winner)
		{
			last_live_of_winner = ((ls->players)[i])->last_live;
			winner_num = i + 1;
		}
		i++;
	}
	if (ls->args->fl_visual == 0)
		print_winner(ls, winner_num);
	if (ls->args->fl_visual == 1)
		end_draw((ls->players)[(winner_num - 1)]);
	exit(0);
}

int					calculate_processes_and_0lives(t_proc *proc)
{
	int sum;

	sum = 0;
	while (proc)
	{
		sum++;
		proc->is_alive = FALSE;
		proc = proc->next;
	}
	return (sum);
}

void				debug_8(t_core *ls, size_t a, size_t b, size_t c)
{
	if (ls->args->num_debug & 8)
	{
		ft_putstr("Process ");
		ft_putnbr_u(a);
		ft_putstr(" hasn't lived for ");
		ft_putnbr_u(b);
		ft_putstr(" cycles (CTD ");
		ft_putnbr_u(c + CYCLE_DELTA);
		ft_putendl(")");
	}
}

int					kill_processes(t_proc **head, t_core *ls)
{
	t_proc	*ptr;
	t_proc	*t;

	ptr = *head;
	while (ptr)
	{
		if (ptr == *head && !(ptr->is_alive))
		{
			t = ptr;
			*head = ptr->next;
			ptr = *head;
			debug_8(ls, t->number, ls->cycle - t->alive_at, ls->cycle_to_die);
			ft_strdel((char **)&(t));
		}
		else if (ptr->next && !(ptr->next->is_alive))
		{
			t = ptr->next;
			ptr->next = ptr->next->next;
			debug_8(ls, t->number, ls->cycle - t->alive_at, ls->cycle_to_die);
			ft_memdel((void **)&(t));
		}
		else
			ptr = ptr->next;
	}
	return (calculate_processes_and_0lives(*head));
}
