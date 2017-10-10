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

int		vm_check_magic_byte(int fd)
{
	char magic_byte[10];

	magic_byte[9] = '\0';
	if (lseek(fd, 0, 0) < 0)
		ft_exit("Error lseek");
	if ((read(fd, magic_byte, 10)) < 0)
		ft_exit("Cannot read file");
	//if(!ft_strnstr(magic_byte, "00ea 83f3", 9))
	//	ft_exit("Error: in magic byte, my friend!");
}

int 	vm_power(char *chr, int pow)
{
	int sum;
	int num;

	num = ft_atoi(chr);
	while (pow > 0)
	{

		sum *= num;
		pow--;
	}
	return (sum);
}

char	vm_conv_hex_to_ascii(t_player *player, char *name, int size)
{

	int		chr;
	int		i;
	int		j;
	char	*tmp;
	char 	buffer[size];

	i = 0;
	j = 0;
	chr = 0;
	while (name[i] != '\0')
	{
		if (name[i] == ' ' || name[i] == '\n')
		{
			i++;
			continue;
		}
		else
		{
			if (name[i] == 48 && name[i + 1] == 48)
			{
				i += 2;
				continue;
			}
			if (name[i] >= 48 && name[i] <= 57)
				chr = ((name[i] - 48) * 16);
			if (name[i + 1] >= 48 && name[i + 1] <= 57)
				chr += ((name[i + 1] - 48));
			if (name[i] >= 97 && name[i] <= 122)
				chr = ((name[i] - 49));
			if (name[i + 1] >= 97 && name[i + 1] <= 122)
				chr += ((name[i + 1] - 49) * 16);
//			printf("%c\n", chr);
		}
		buffer[j] = chr;
		j++;
		i += 2;
	}
	player->name = ft_strdup(buffer);
}

void	vm_add_name(t_player *player, char *name)
{

	vm_conv_hex_to_ascii(player, name, 129);

}

int 	vm_check_null(char *buffer, int pos1, int pos2)
{
	if (buffer[pos1] !=  48 || buffer[pos2] != 48)
		ft_exit("Error not valid data");
}

void	vm_hndl_name(t_player *player, int fd)
{
	char buffer[331];

	buffer[330] = '\0';
	lseek(fd, 10, 0);
	read(fd, buffer, 330);
	vm_check_null(buffer, 328, 327);
	vm_add_name(player, buffer);
}

void	vm_read_bot_data(t_player *player)
{

	vm_check_magic_byte(player->fd);
	vm_hndl_name(player, player->fd);
//	while (line[j] != '\0')
//	{
//
//		((j % 4) == 0 && line[j] != ' ') ? octet++ : octet ;
//		if (line[j] != ' ')
//			printf("%c->%i ", line[j], octet);
//
//		j++;
//	}
//	printf("\nEND LINE");
//	char *cur;
//	if(i == 0)
//	{
//	//	bot_hndl_name()
//	}
//
}

int		vm_check_size_file(int fd)
{
	int i;
	char buffer[331];
	i = 0;
	char *str_name;
	buffer[330] = '\0';


	size_t offset;
	offset = lseek(fd, 0, SEEK_END);
	//if (offset > 10000)
		// ft_exit("Too large file, my friend");

	//ft_exit("s");
}

int		vm_read_bot(t_arg *ptr, int i)
{
	int		fd;

	fd = open(ptr->path_players[i], O_RDONLY, 0666);
	if (fd < 0)
		ft_exit("Not exist file *.cor");
	ptr->player[i]->fd = fd;
	vm_check_size_file(fd);
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

