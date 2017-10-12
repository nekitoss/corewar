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

int		find_ext_to_end(char *argv)
{
	int		i;
	char	*ptr;
	char	*cor;

	i = 0;
	cor = ".cor";
	ptr = argv;
	if ((ft_strlen(argv)) < 4)
		return (1);
	while (argv[i] != '\0')
	{
		ptr++;
		i++;
	}
	ptr -= 4;
	if (!ft_strcmp(cor, ptr))
		return (0);
	return (1);
}

int		ft_isdigit_str(char *argv)
{
	int i;

	i = 0;
	while (argv[i] != '\0')
	{
		if(!(ft_isdigit(argv[i])))
			return (1);
		i++;
	}
	return (0);
}

void sv_number_player(char *argv, t_arg *ptr, int *fl)
{
	int tmp;

	if (ft_isdigit_str(argv))
		ft_exit("Not correct value of number player");
	tmp = ft_atoi(argv);
	if (tmp > MAX_PLAYERS || tmp <= 0)
		ft_exit("Not correct number player");
	ptr->num[ptr->cnt_player] = tmp;
	(*fl)++;
}

void 	sv_path_player(char *argv, t_arg *ptr, int *fl)
{
	if (ptr->cnt_player <= 3)
		ptr->path_players[ptr->cnt_player] = ft_strdup(argv);
	if (ptr->cnt_player > 3)
		ft_exit("Too many champions");
	ptr->cnt_player++;
	if (*fl == 2)
		(*fl) = 0;
}


