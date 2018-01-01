/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_save_data_bot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 13:38:08 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/10 13:38:09 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	hndl_cmd_arg_original(char **argv, t_arg *ptr, char *str)
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
		ptr->fl_original = 1;
	else if (cnt > 1)
		ft_exit("Error: too many flags\n");
}

void	hndl_cmd_arg_music(char **argv, t_arg *ptr, char *str)
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
		ptr->fl_music = 1;
	else if (cnt > 1)
		ft_exit("Error: too many flags\n");
}

void	ft_save_val_debug(t_arg *ptr, char **argv, int i, char **cur)
{
	size_t num;

	ptr->fl_debug = 1;
	if (ft_strlen(argv[(i + 1)]) > 10)
		ft_exit("Error: too big number for debug number, my friend\n");
	if (**cur != '0')
	{
		num = (size_t)ft_atoi(*cur);
		if (ft_strcmp(*cur, ft_itoa(num)))
			ft_exit("Error: to big number for debug number, my friend\n");
		if (num > 2147483647)
			ft_exit("Error: to big number for debug number, my friend\n");
		ptr->num_debug = num;
	}
	else
		ptr->num_debug = (size_t)ft_atoi(*cur);
}

int		hndl_cmd_arg_debug(char **argv, t_arg *ptr, char *str)
{
	int		i;
	char	*cur;

	i = 1;
	while (i < ptr->cnt_arg)
	{
		if (!ft_strcmp(str, argv[i]))
		{
			if (i + 1 >= ptr->cnt_arg)
				ft_exit("Error: incorrect value of debug\n");
			if (!valid_val_arg(argv[(i + 1)], &cur))
			{
				ft_save_val_debug(ptr, argv, i, &cur);
			}
			else
				ft_exit("Error: incorrect value of debug\n");
		}
		i++;
	}
	return (0);
}

void	vm_hndl_code(t_player *player, int fd)
{
	char		buffer[CHAMP_MAX_SIZE + 1];
	long int	offset;

	buffer[CHAMP_MAX_SIZE] = '\0';
	offset = lseek(fd, 0, SEEK_END);
	if ((offset - 2192) != player->size_code)
	{
		ft_exit_name_file(player, "Error file: ",
			" has a code size that differ from what its header says\n");
	}
	else if (offset > 2874)
		ft_exit_size_code(player, "File ", " has too large a code (",
			" bytes > 682 bytes)\n");
	lseek(fd, 2192, SEEK_SET);
	read(fd, buffer, player->size_code);
	player->program_code = (unsigned char *)malloc(sizeof(char) *
		(player->size_code) + 1);
	player->program_code[(player->size_code)] = '\0';
	ft_memcpy((void*)player->program_code, buffer, player->size_code);
}
