/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochuka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:41:17 by mpochuka          #+#    #+#             */
/*   Updated: 2017/10/27 21:41:17 by mpochuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int					read_4_byte(t_core *ls, unsigned int start)
{
	int	res;

	res = ls->field[(start % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 1) % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 2) % MEM_SIZE)];
	res = res << OCTET;
	res |= ls->field[((start + 3) % MEM_SIZE)];
	return (res);
}

int					read_data_block(t_core *ls, unsigned int start, int len)
{
	int res;

	res = 0;
	if (len == 1)
		res = (int)read_1_byte(ls, start);
	else if (len == 2)
		res = (int)read_2_byte(ls, start);
	else if (len == 4)
		res = read_4_byte(ls, start);
	else if (len == 0)
		res = 0;
	return (res);
}

void				print_data(unsigned char *str, size_t len, size_t width)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (i != 0 && i % width == 0)
			ft_putendl("");
		hex_print(str[i]);
		i++;
	}
	ft_putendl("");
}

void				shift_pc(size_t *pc, unsigned int value)
{
	(*pc) = (*pc) + value;
	(*pc) = (*pc) % MEM_SIZE;
}

void				set_next_ex(size_t *next_execution_at, int value)
{
	(*next_execution_at) = (*next_execution_at) + value;
}
