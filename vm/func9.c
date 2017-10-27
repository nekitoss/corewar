/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochuka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:43:26 by mpochuka          #+#    #+#             */
/*   Updated: 2017/10/27 21:43:26 by mpochuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void				print_winner(t_core *ls, int winner_num)
{
	ft_putstr("GAME_ENDED on cycle");
	ft_putnbr_u(ls->cycle);
	ft_putendl("");
	ft_putstr("The winner is: player ");
	ft_putnbr(winner_num);
	ft_putstr(", \"");
	ft_putstr(((ls->players)[(winner_num - 1)])->name);
	ft_putendl("\"");
}

void				free_players(t_core *ls)
{
	int i;

	i = 0;
	while (i < ls->num_of_players)
	{
		ft_strdel(&(((ls->players)[i])->name));
		ft_strdel(&(((ls->players)[i])->comment));
		if (((ls->players)[i])->program_code)
			free(((ls->players)[i])->program_code);
		ft_strdel(&(((ls->players)[i])->path_player));
	}
	free(ls->players);
	ls->players = NULL;
}

void				free_proc(t_proc *pr)
{
	if (pr->next)
		free_proc(pr->next);
	free(pr);
}

void				free_core(t_core *ls)
{
	if (ls)
	{
		if (ls->players)
			free_players(ls);
		if (ls->processes_list)
			free_proc(ls->processes_list);
		ls->processes_list = NULL;
		if (ls->args)
			free(ls->args);
		ls->args = NULL;
		free(ls);
	}
}
