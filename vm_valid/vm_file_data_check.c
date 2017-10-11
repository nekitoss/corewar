/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_file_data_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:34:29 by mkurchin          #+#    #+#             */
/*   Updated: 2017/10/11 20:34:30 by mkurchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		vm_check_magic_byte(int fd)
{
	unsigned int magic_byte;
	unsigned int num;

	magic_byte = 4085508608;
	if (lseek(fd, 0, 0) < 0)
		ft_exit("Error lseek");
	if ((read(fd, &num, 4)) < 0)
		ft_exit("Cannot read file");
	if (magic_byte != num)
		ft_exit("Error in magic byte, my friend!");
}

int 	vm_check_null(int fd)
{
	int zero;

	zero = 0;
	read(fd, &zero, 4);
	if (zero != 0)
		ft_exit("Error not valid data, don't have null terminate");
}

void	vm_hndl_name(t_player *player, int fd)
{
	char buffer[129];

	buffer[128] = '\0';
	lseek(fd, 4, 0);
	read(fd, buffer, PROG_NAME_LENGTH);
	vm_check_null(fd);
	player->name = ft_strdup(buffer);
}

void	vm_hndl_comment(t_player *player, int fd)
{
	char buffer[COMMENT_LENGTH + 1];

	buffer[COMMENT_LENGTH] = '\0';
	lseek(fd, 140, 0);
	read(fd, buffer, COMMENT_LENGTH);
	vm_check_null(fd);
	player->comment = ft_strdup(buffer);
}

void	vm_hndl_size_code(t_player *player, int fd)
{
	int num;
	int swapped;

	lseek(fd, 136, 0);
	read(fd, &num, 4);
	swapped = ((num>>24)&0xff) |
			  ((num<<8)&0xff0000) |
			  ((num>>8)&0xff00) |
			  ((num<<24)&0xff000000);
	player->size_code = swapped;
}
