/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochuka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:41:09 by mpochuka          #+#    #+#             */
/*   Updated: 2017/10/27 21:41:09 by mpochuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

short				revert_16_bits_size_t(short num)
{
	num = (num >> 8) | (num << 8);
	return (num);
}

int					revert_32_bits_size_t(int num)
{
	num = ((num >> 24) & 0xff) |
			((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) |
			((num << 24) & 0xff000000);
	return (num);
}

void				write_data_block(t_proc *proc, int data, unsigned int start,
																		int len)
{
	int i;

	i = 0;
	if (len == 4)
		data = revert_32_bits_size_t(data);
	else if (len == 2)
		data = revert_16_bits_size_t(data);
	while (i < len && i < 5)
	{
		proc->ls->field[((start + i) % MEM_SIZE)] = (data & 0xff);
		proc->ls->colors[((start + i) % MEM_SIZE)] = proc->belong_to_player;
		data = data >> OCTET;
		i++;
	}
}

char				read_1_byte(t_core *ls, unsigned int start)
{
	char res;

	res = ls->field[(start % MEM_SIZE)];
	return (res);
}

short				read_2_byte(t_core *ls, unsigned int start)
{
	short res;

	res = ls->field[(start % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 1) % MEM_SIZE)];
	return (res);
}
