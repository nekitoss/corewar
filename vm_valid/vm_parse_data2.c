/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse_data2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:34:39 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/27 18:34:40 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		valid_val_arg(char *argv, char **cur)
{
	*cur = argv;
	while (**cur != '\0')
	{
		if (ft_isdigit(**cur))
		{
			if (**cur == '0')
			{
				(*cur)++;
				continue ;
			}
			break ;
		}
		else
			return (1);
	}
	if (**cur == '\0')
	{
		(*cur)--;
		return (0);
	}
	return (0);
}

void	hndl_cmd_arg_n(char **argv, t_arg *ptr)
{
	int		i;
	char	*cur;

	i = 0;
	while (i < ptr->cnt_arg)
	{
		if (!ft_strcmp("-n", argv[i]))
		{
			if ((i + 1) < ptr->cnt_arg)
			{
				if (valid_val_arg(argv[(i + 1)], &cur))
					ft_exit("Error: not valid arg, my friend\n");
				if (ft_strlen(argv[(i + 1)]) > 10)
					ft_exit("Error: too big number, my friend\n");
			}
			else
				ft_exit("Error: incorrect value of number player\n");
		}
		i++;
	}
}

void	srch_dublicate_num_player(t_arg *ptr)
{
	int i;
	int j;

	i = 0;
	while (i < ptr->cnt_player)
	{
		if (ptr->num[i] > ptr->cnt_player || ptr->num[i] <= 0)
			ft_exit("Not correct number of player\n");
		j = i + 1;
		while (j < ptr->cnt_player)
		{
			if (ptr->num[i] == ptr->num[j])
				ft_exit("Error: dublicate number of player\n");
			j++;
		}
		i++;
	}
}

int		ft_parse_cmd_line(t_arg *ptr, char **argv, int *fl, int *i)
{
	if (!ft_strcmp("-n", argv[*i]))
		(*fl)++;
	else if (!find_ext_to_end(argv[*i]) && *fl == 0)
		sv_path_player(argv[*i], ptr, fl);
	else if (!find_ext_to_end(argv[*i]) && *fl == 2)
		sv_path_player(argv[*i], ptr, fl);
	else if (*fl == 1)
		sv_number_player(argv[*i], ptr, fl);
	else if (!ft_strcmp("-dump", argv[*i]) || !ft_strcmp("-w", argv[*i]) ||
		!ft_strcmp("-debug", argv[*i]))
	{
		(*i) += 2;
		return (3);
	}
	else if (!ft_strcmp("-v", argv[*i]) || !ft_strcmp("-m", argv[*i]) ||
		!ft_strcmp("-o", argv[*i]))
	{
		(*i)++;
		return (3);
	}
	else
		ft_exit("Error: invalid argument in cmd line, think about this\n");
	return (0);
}
