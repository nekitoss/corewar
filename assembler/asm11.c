/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm11.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:16:04 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/19 18:46:34 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		write_param(int fd, t_commands *comm, t_label *lb, int i)
{
	if (comm->p[i] == 'R')
		write_reg(fd, comm->param[i]);
	else if (comm->p[i] == 'I')
		write_indir(fd, comm, lb, i);
	else if (comm->p[i] == 'D')
		write_dir(fd, comm, lb, i);
	else if (comm->p[i] == 'd')
		write_indir(fd, comm, lb, i);
	else
		return ;
}

void		write_to_cor(int fdwrite, t_commands *comm, t_label *lb)
{
	int		i;

	i = g_tab[get_ind(comm->command_name)].op_code;
	write(fdwrite, &i, 1);
	if (g_tab[get_ind(comm->command_name)].codage)
		write_codage(fdwrite, comm);
	write_param(fdwrite, comm, lb, 0);
	write_param(fdwrite, comm, lb, 1);
	write_param(fdwrite, comm, lb, 2);
}

void		make_corfile(t_asm *masm, t_commands *comm, t_label *lb, char *name)
{
	int		fdwrite;
	char	*n;

	n = make_name(name);
	fdwrite = open(n, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	masm->head->prog_size = reverse_bit((unsigned)masm->count_byte);
	write(fdwrite, masm->head, sizeof(t_header));
	while (comm)
	{
		write_to_cor(fdwrite, comm, lb);
		comm = comm->next;
	}
	ft_putstr("Writing output program to ");
	ft_putstr(n);
	ft_putchar('\n');
	free(n);
	close(fdwrite);
}

int			find_lb(char *s, t_label *lb)
{
	while (lb)
	{
		if (ft_strequ(lb->name, s))
			return (1);
		lb = lb->next;
	}
	return (0);
}

void		check_lb(t_commands *comm, t_label *lb)
{
	int		i;

	while (comm)
	{
		i = 0;
		while (i < 3)
		{
			if (comm->labels[i] != NULL)
				if (!find_lb(comm->labels[i], lb))
					error("ERROR. No such label.");
			i++;
		}
		comm = comm->next;
	}
}
