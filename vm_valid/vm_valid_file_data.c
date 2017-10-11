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
	int magic_byte;
	int num;
//ea83f3
	magic_byte = 15369203;
	if (lseek(fd, 0, 0) < 0)
		ft_exit("Error lseek");
	while ()
	if ((read(fd, &num, 4)) < 0)
		ft_exit("Cannot read file");
	//if(magic_byte != num)
	//	ft_exit("Error: in magic byte, my friend!");
}

int 	vm_power(char chr, int pow)
{
	int sum;
	int num;

	num = 0;
	if (chr == '\0')
		return (num);
	num = ft_atoi(&chr);
	sum = 16;
	while (pow > 1)
	{
		sum *= 16;
		pow--;
	}
	if (pow == 1)
		sum = 16;
	return (sum + num);
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

//void	vm_add_name(t_player *player, char *name)
//{
//	vm_conv_hex_to_ascii(player, name, 129);
//}

int 	vm_check_null(char *buffer, int pos1, int pos2)
{
	if (buffer[pos1] !=  48 || buffer[pos2] != 48)
		ft_exit("Error not valid data");
}

void	vm_hndl_name(t_player *player, int fd)
{
	char buffer[129];

	buffer[128] = '\0';
	lseek(fd, 4, 0);
	read(fd, buffer, PROG_NAME_LENGTH);
	///vm_check_null(buffer, 328, 327);
	player->name = ft_strdup(buffer);
	//vm_add_name(player, buffer);
}

void	vm_hndl_comment(t_player *player, int fd)
{
	char buffer[COMMENT_LENGTH + 1];

	buffer[COMMENT_LENGTH] = '\0';
	lseek(fd, 140, 0);
	read(fd, buffer, COMMENT_LENGTH);
	player->comment = ft_strdup(buffer);
	//vm_check_null(buffer, 328, 327);


}

void	vm_calc_hex_to_int(char *str)
{
	int i;
	int len;
	int sum;

	len = 0;
	i = 0;
	sum = 0;
	len = ft_strlen(str);
	len--;
	while (str[i] != '\0')
	{

		sum += vm_power(str[i], len);
		i++;
		len--;
	}
}

void 	vm_add_size_code(t_player *player, char *buffer)
{
	int		i;
	int		j;
	char	tmp[9];

	tmp[8] = '\0';
	i = 0;
	j = 0;

	while(buffer[i] != NULL)
	{
		if (buffer[i] == ' ')
		{
			i++;
			continue;
		}
		tmp[j] = buffer[i];
		j++;
		i++;
	}
	vm_calc_hex_to_int(tmp);
}

void	vm_hndl_size_code(t_player *player, int fd)
{
	int num;
	int swapped;

	lseek(fd, 136, 0);
	read(fd, &num, 4);
	swapped = ((num>>24)&0xff) | // move byte 3 to byte 0
			  ((num<<8)&0xff0000) | // move byte 1 to byte 2
			  ((num>>8)&0xff00) | // move byte 2 to byte 1
			  ((num<<24)&0xff000000);
	player->size_code = swapped;

}

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


//	vm_hndl_comment(player, player->fd);
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

