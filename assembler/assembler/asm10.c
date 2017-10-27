/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm10.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:15:26 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/19 18:46:24 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int		reverse_two_bit(unsigned int a)
{
	unsigned int	b;

	b = 0;
	b = b | (a & 255);
	b = b << 8;
	a = a >> 8;
	b = b | (a & 255);
	return (b);
}

void				write_reg(int fd, int param)
{
	write(fd, &param, 1);
}

int					get_length(int curr_byte, int lb_byte, int fl)
{
	unsigned int	res;

	if (lb_byte >= curr_byte)
		res = (unsigned)lb_byte - curr_byte;
	else
	{
		if (fl == 4)
		{
			res = 4294967295;
			res = res - (curr_byte - lb_byte) + 1;
		}
		else
		{
			res = 65535;
			res = res - (curr_byte - lb_byte) + 1;
		}
	}
	return (res);
}

void				write_indir(int fd, t_commands *comm, t_label *lb, int i)
{
	int				param;

	if (comm->labels[i] == NULL)
		param = comm->param[i];
	else
	{
		while (!ft_strequ(comm->labels[i], lb->name) && lb)
		{
			lb = lb->next;
		}
		param = get_length(comm->size, lb->byte_num, 2);
	}
	param = reverse_two_bit((unsigned)param);
	write(fd, &param, 2);
}

void				write_dir(int fd, t_commands *comm, t_label *lb, int i)
{
	int				param;

	if (comm->labels[i] == NULL)
		param = comm->param[i];
	else
	{
		while (!ft_strequ(comm->labels[i], lb->name) && lb)
		{
			lb = lb->next;
		}
		param = get_length(comm->size, lb->byte_num, 4);
	}
	param = reverse_bit((unsigned)param);
	write(fd, &param, 4);
}
