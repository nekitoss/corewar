/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:52:36 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/27 20:52:37 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_save_val_width(t_arg *ptr, char **argv, int i, char **cur)
{
	size_t num;

	ptr->fl_width = 1;
	if (ft_strlen(argv[(i + 1)]) > 10)
		ft_exit("Error: too big number, my friend\n");
	if (**cur != '0')
	{
		num = (size_t)ft_atoi(*cur);
		if (ft_strcmp(*cur, ft_itoa(num)))
			ft_exit("Error: to big number, my friend\n");
		if (num == 0)
			ft_exit("Error: number must be not zero, my friend\n");
		ptr->width_dump = num;
	}
	else
		ptr->width_dump = (size_t)ft_atoi(*cur);
}

void	ft_save_val_dump(t_arg *ptr, char **argv, int i, char **cur)
{
	size_t num;

	ptr->fl_dump = 1;
	if (ft_strlen(argv[(i + 1)]) > 10)
		ft_exit("Error: too big number, my friend\n");
	if (**cur != '0')
	{
		num = (size_t)ft_atoi(*cur);
		if (ft_strcmp(*cur, ft_itoa(num)))
			ft_exit("Error: to big number, my friend\n");
		if (num > 2147483647)
			ft_exit("Error: to big number, my friend\n");
		ptr->num_dump = num;
	}
	else
		ptr->num_dump = (size_t)ft_atoi(*cur);
}

int		hndl_cmd_arg_dump(char **argv, t_arg *ptr, char *str)
{
	int		i;
	char	*cur;

	i = 1;
	while (i < ptr->cnt_arg)
	{
		if (!ft_strcmp(str, argv[i]))
		{
			if (i + 1 >= ptr->cnt_arg)
				ft_exit("Error: incorrect value of dump\n");
			if (!valid_val_arg(argv[(i + 1)], &cur))
			{
				ft_save_val_dump(ptr, argv, i, &cur);
			}
			else
				ft_exit("Error: incorrect value of dump\n");
		}
		i++;
	}
	return (0);
}

void	vm_valid_arg(int argc, char **argv, t_arg *ptr)
{
	ptr->cnt_arg = argc;
	hndl_cmd_arg_dump(argv, ptr, "-dump");
	hndl_cmd_arg_debug(argv, ptr, "-debug");
	hndl_cmd_arg_visual(argv, ptr, "-v");
	hndl_cmd_arg_music(argv, ptr, "-m");
	hndl_cmd_arg_wide(argv, ptr, "-w");
	hndl_cmd_arg_original(argv, ptr, "-o");
	hndl_cmd_arg_n(argv, ptr);
	valid_filename(argv, ptr);
	valid_flags(ptr);
	set_num_player(ptr);
	srch_dublicate_num_player(ptr);
}

t_arg	*vm_valid(int argc, char **argv)
{
	t_arg	*ptr;

	vm_init_struct(&ptr);
	vm_valid_arg(argc, argv, ptr);
	vm_init_struct_player(&ptr);
	vm_valid_data_file(ptr);
	return (ptr);
}
