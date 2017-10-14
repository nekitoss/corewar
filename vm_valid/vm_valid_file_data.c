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

void 	ft_exit_name_file(t_player *player, char *str1, char *str2)
{
	write(1, str1, ft_strlen(str1));
	write(1, player->path_player, ft_strlen(player->path_player));
	write(1, str2, ft_strlen(str2));
	exit(0);
}

void	vm_check_file_structure(t_player *player)
{
	int offset;

	if (offset = lseek(player->fd,0,SEEK_END) < 0)
		ft_exit("Error lseek");
	if (offset == 0)
	{
		// insert free func!!!
		ft_exit_name_file(player, "Error file too small: ", " it's "
				"empty");
	}
	else if (offset < 4 )
		ft_exit_name_file(player, "Error file too small: ", "have'not magic number");
	else if (offset < 132 && offset > 4)
		ft_exit_name_file(player, "Error file too small: ", "have'not correct name");
	else if (offset < 140 && offset > 136)
		ft_exit_name_file(player, "Error file too small: ", "have'not size code");
	else if (offset > 140 && offset < 2192)
		ft_exit_name_file(player, "Error file too small: ", "have'not comment");
}

void 	vm_hndl_code(t_player *player, int fd)
{
	char buffer[CHAMP_MAX_SIZE + 1];
	int byte;
	long int offset;

	buffer[CHAMP_MAX_SIZE] = '\0';
	offset = lseek(fd,0,SEEK_END);
	if ((offset - 2192) != player->size_code)
	{
		ft_exit_name_file(player, "Error file: ",
		  " has a code size that differ from what its header says\n");
	}
	else if (offset > 2874)
		ft_exit("Too big code size bot");
	player->program_code = (char*)malloc(sizeof(char) * byte + 1);
	player->program_code[byte] = '\0';
	ft_memcpy((void*)player->program_code, (void*)buffer, byte);
}

void	vm_read_bot_data(t_player *player)
{
	vm_check_file_structure(player);
	vm_check_magic_byte(player->fd);
	vm_hndl_name(player, player->fd);
	vm_hndl_size_code(player, player->fd);
	vm_hndl_comment(player, player->fd);
	vm_hndl_code(player, player->fd);
}

void	vm_read_bot(t_arg *ptr, int i)
{
	int		fd;
	char	chr;
	long long int offset; // test
	fd = open(ptr->path_players[i], O_RDONLY, 0666);
	offset = lseek(fd,0,SEEK_END);//test
	read(fd,&chr,1);// test
	if (fd < 0)
		ft_exit("Not exist file *.cor");
	ptr->player[i]->fd = fd;
	ptr->player[i]->path_player = ptr->path_players[i];
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

