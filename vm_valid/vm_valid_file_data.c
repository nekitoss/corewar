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

void	ft_exit_size_code(t_player *player, char *str1, char *str2, char *str3)
{
	char *size_code;

	size_code = ft_itoa(player->size_code);
	write(1, str1, ft_strlen(str1));
	write(1, player->path_player, ft_strlen(player->path_player));
	write(1, str2, ft_strlen(str2));
	write(1, size_code, ft_strlen(size_code));
	write(1, str3, ft_strlen(str3));
	exit(0);
}

void	vm_check_file_structure(t_player *player)
{
	long int offset;

	if ((offset = lseek(player->fd, 0, SEEK_END)) < 0)
		ft_exit("Error lseek\n");
	if (offset == 0)
	{
		ft_exit_name_file(player, "Error: file too small: ", " it's "
		"empty my friend\n");
	}
	else if (offset < 4)
		ft_exit_name_file(player, "Error: file too small: ", "have'not magic nu"
			"mber\n");
	else if (offset < 132 && offset > 4)
		ft_exit_name_file(player, "Error: file too small: ", "have'not correct "
			"name\n");
	else if (offset < 140 && offset > 136)
		ft_exit_name_file(player, "Error: file too small: ", "have'not size cod"
			"e\n");
	else if (offset > 140 && offset < 2192)
		ft_exit_name_file(player, "Error: file too small: ", "have'not comment"
			"\n");
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

	fd = open(ptr->path_players[i], O_RDONLY, 0666);
	if (fd < 0)
		ft_exit("Not exist file *.cor\n");
	ptr->player[i]->fd = fd;
	ptr->player[i]->path_player = ptr->path_players[i];
	vm_read_bot_data(ptr->player[i]);
}

int		vm_valid_data_file(t_arg *ptr)
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
