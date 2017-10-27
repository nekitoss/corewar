/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm7.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/16 19:05:37 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			add_reg(t_commands *comm, int i, char **s)
{
	(*s)++;
	comm->param[i] = ft_atoi(*s);
	comm->p[i] = 'R';
	return (1);
}

int			add_indir(t_commands *comm, int i, char **s)
{
	if (**s == ':')
		(*s)++;
	comm->p[i] = 'I';
	if (**s == '-' || ft_isdigit(**s))
		comm->param[i] = ft_atoi(*s);
	else
		comm->labels[i] = get_lb_name(*s);
	return (2);
}

int			add_lbdir(t_commands *comm, int i, int ind, char **s)
{
	(*s)++;
	comm->labels[i] = get_lb_name(*s);
	if (!g_tab[ind].dir_size)
	{
		comm->p[i] = 'D';
		return (4);
	}
	else
	{
		comm->p[i] = 'd';
		return (2);
	}
}

int			add_dir(t_commands *comm, int i, int ind, char **s)
{
	(*s)++;
	if (**s == ':')
		return (add_lbdir(comm, i, ind, s));
	comm->param[i] = ft_atoi(*s);
	if (!g_tab[ind].dir_size)
	{
		comm->p[i] = 'D';
		return (4);
	}
	else
	{
		comm->p[i] = 'd';
		return (2);
	}
}

int			set_param(t_commands *comm, int i, int index, char **s)
{
	int		k;

	k = check_type(s, i, index);
	if (k == 1)
		return (add_reg(comm, i, s));
	else if (k == 2)
		return (add_dir(comm, i, index, s));
	else if (k == 4)
		return (add_indir(comm, i, s));
	return (0);
}
