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

void 	vm_hndl_code(t_player *player, int fd)
{
	char buffer[CHAMP_MAX_SIZE + 1];
	long int offset;

	buffer[CHAMP_MAX_SIZE] = '\0';
	offset = lseek(fd,0,SEEK_END);
	if ((offset - 2192) != player->size_code)
	{
		ft_exit_name_file(player, "Error file: ",
			" has a code size that differ from what its header says\n");
	}
	else if (offset > 2874)
		ft_exit_size_code(player, "File ", " has too large a code (",
						  " bytes > 682 bytes)\n");
	read (fd, buffer, player->size_code);
	player->program_code = (unsigned char *)malloc(sizeof(char) *
		(player->size_code) + 1);
	player->program_code[(player->size_code)] = '\0';
	ft_memcpy((void*)player->program_code, buffer, player->size_code);
}



