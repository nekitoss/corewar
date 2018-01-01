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

void	vm_check_magic_byte(int fd)
{
	unsigned int magic_byte;
	unsigned int num;

	magic_byte = 4085508608;
	if (lseek(fd, 0, 0) < 0)
		ft_exit("Error lseek\n");
	if ((read(fd, &num, 4)) < 0)
		ft_exit("Error: cannot read file\n");
	if (magic_byte != num)
		ft_exit("Error in magic byte, my friend!\n");
}

void	vm_check_null(int fd, int fl)
{
	int zero;

	zero = 0;
	read(fd, &zero, 4);
	if (zero != 0)
	{
		if (fl == 1)
		{
			ft_putstr("Warning: "
					"don't have null terminate afte name. Autocorrect\n");
		}
		if (fl == 2)
			ft_putstr("Warning: "
					"don't have null terminate afte comment. Autocorrect\n");
	}
}

void	vm_hndl_name(t_player *player, int fd)
{
	char buffer[129];

	buffer[128] = '\0';
	if (lseek(fd, 4, 0) < 0)
		ft_exit("Error lseek\n");
	read(fd, buffer, PROG_NAME_LENGTH);
	vm_check_null(fd, 1);
	player->name = ft_strdup(buffer);
}

void	vm_hndl_comment(t_player *player, int fd)
{
	char buffer[COMMENT_LENGTH + 1];

	buffer[COMMENT_LENGTH] = '\0';
	if (lseek(fd, 140, 0) < 0)
		ft_exit("Error lseek\n");
	read(fd, buffer, COMMENT_LENGTH);
	vm_check_null(fd, 2);
	player->comment = ft_strdup(buffer);
}

void	vm_hndl_size_code(t_player *player, int fd)
{
	int num;
	int swapped;

	lseek(fd, 136, 0);
	read(fd, &num, 4);
	swapped = ((num >> 24) & 0xff) |
		((num << 8) & 0xff0000) |
		((num >> 8) & 0xff00) |
		((num << 24) & 0xff000000);
	player->size_code = swapped;
}
