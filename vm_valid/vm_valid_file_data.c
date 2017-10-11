/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_valid_file_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:52:15 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/07 13:52:29 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"



void 	vm_hndl_code(t_player *player, int fd)
{
	char buffer[CHAMP_MAX_SIZE + 1];
	int byte;

	buffer[CHAMP_MAX_SIZE] = '\0';
	lseek(fd, 2192, 0);
	if ((byte = read(fd, buffer, player->size_code)) > 0)
	{
		if (read(fd, buffer, 1) != 0)
			ft_exit("Not correct size code champ bot");
		player->program_code = (char*)malloc(sizeof(char) * byte + 1);
		player->program_code[byte] = '\0';
		ft_memcpy((void*)player->program_code, (void*)buffer, byte);
	}
	else
		ft_exit("Don't have code bot or error of read");
}

void	vm_read_bot_data(t_player *player)
{
	vm_check_magic_byte(player->fd);
	vm_hndl_name(player, player->fd);
	vm_hndl_size_code(player, player->fd);
	vm_hndl_comment(player, player->fd);
	vm_hndl_code(player, player->fd);
}

int		vm_read_bot(t_arg *ptr, int i)
{
	int		fd;

	fd = open(ptr->path_players[i], O_RDONLY, 0666);
	if (fd < 0)
		ft_exit("Not exist file *.cor");
	ptr->player[i]->fd = fd;
	vm_read_bot_data(ptr->player[i]);
}

int     vm_valid_data_file(t_arg *ptr)
{
	int i;

	i = 0;
	while (i < ptr->cnt_player)
	{
		vm_read_bot(ptr, i);
		i++;
	}
	return (0);
}

