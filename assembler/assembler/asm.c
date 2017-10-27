/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:17:46 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/27 20:48:42 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main(int argc, char **argv)
{
	int			fd;
	char		*file;
	t_asm		*mstruc;
	char		*start;

	if (argc != 2)
		error("No filename. Usage: ./asm filename.");
	fd = check_file_name(argv[argc - 1]);
	file = read_file(fd);
	mstruc = new_struct();
	mstruc->head = new_head();
	mstruc->labels->byte_num = -1;
	start = ft_strdup("start");
	mstruc->commands->command_name = start;
	valid_code(mstruc, file, mstruc->head);
	check_lb(mstruc->commands, mstruc->labels);
	make_corfile(mstruc, mstruc->commands, mstruc->labels, argv[argc - 1]);
	close(fd);
	free(start);
	free(file);
	return (0);
}

void			free_main(t_asm *mstruc)
{
	free_lb(mstruc->labels);
	free(mstruc->labels);
	free_comm(mstruc->commands);
	free(mstruc->commands);
	free(mstruc->head);
	free(mstruc);
}

void			free_lb(t_label *lb)
{
	if (lb->next)
		free_lb(lb->next);
	free(lb->name);
	if (lb->next)
		free(lb->next);
}

void			free_comm(t_commands *comm)
{
	if (comm->next)
		free_comm(comm->next);
	if (comm->next)
		free(comm->next);
	free(comm->param);
	free(comm->p);
	free(comm->labels[0]);
	free(comm->labels[1]);
	free(comm->labels[2]);
	free(comm->labels);
	free(comm->command_name);
}

long long		fft_atoi(const char *str)
{
	long long	result;
	int			is_neg;
	int			i;

	result = 0;
	is_neg = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == 45)
		is_neg = 1;
	if ((str[i] == 45) || (str[i] == 43))
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		result *= 10;
		result += ((int)str[i] - 48);
		i++;
	}
	if (is_neg)
		return (-result);
	else
		return (result);
}
