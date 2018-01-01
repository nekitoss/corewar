/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_valid_cmd_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 20:18:16 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/02 20:18:17 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int			find_ext_to_end(char *argv)
{
	char	*ptr;
	char	*cor;

	cor = ".cor";
	ptr = ft_strrchr(argv, '.');
	if (ptr == NULL)
		return (1);
	if (!ft_strcmp(ptr, cor))
		return (0);
	return (1);
}

int			ft_isdigit_str(char *argv)
{
	int i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (!(ft_isdigit(argv[i])))
			return (1);
		i++;
	}
	return (0);
}

void		sv_number_player(char *argv, t_arg *ptr, int *fl)
{
	int		tmp;
	size_t	num;

	if (ft_isdigit_str(argv))
		ft_exit("Not correct value of number player, my friend\n");
	if (ft_strlen(argv) > 10)
		ft_exit("Error: too big number, my friend, are you joke?)\n");
	num = (size_t)ft_atoi(argv);
	if (ft_strcmp(argv, ft_itoa(num)))
		ft_exit("Error: to big number, my friend\n");
	if (num > 2147483647)
		ft_exit("Error: to big number, my friend\n");
	tmp = ft_atoi(argv);
	if (tmp == 0 || tmp > MAX_PLAYERS)
		ft_exit("Error: not correct number of player, my friend");
	ptr->num[ptr->cnt_player] = tmp;
	(*fl)++;
}

void		sv_path_player(char *argv, t_arg *ptr, int *fl)
{
	if (ptr->cnt_player <= 3)
		ptr->path_players[ptr->cnt_player] = ft_strdup(argv);
	if (ptr->cnt_player > 3)
		ft_exit("Too many champions, it's not football) my friend\n");
	ptr->cnt_player++;
	if (*fl == 2)
		(*fl) = 0;
}

void		hndl_cmd_arg_visual(char **argv, t_arg *ptr, char *str)
{
	int i;
	int cnt;

	i = 1;
	cnt = 0;
	while (i < ptr->cnt_arg)
	{
		if (!ft_strcmp(str, argv[i]))
			cnt++;
		i++;
	}
	if (cnt == 1)
		ptr->fl_visual = 1;
	else if (cnt > 1)
		ft_exit("Error: too many flags\n");
}
