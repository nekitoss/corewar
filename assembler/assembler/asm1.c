/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:06:44 by yrobotko          #+#    #+#             */
/*   Updated: 2017/10/16 19:15:15 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					check_file_name(char *s)
{
	int				fd;
	int				len;

	len = (int)ft_strlen(s);
	if (len <= 2 || s[len - 1] != 's' || s[len - 2] != '.')
		error("Wrong file. File format must be .s");
	fd = open(s, O_RDONLY);
	if (fd < 0)
		error("No file.");
	return (fd);
}

char				*read_file(int fd)
{
	char			*str;
	long long		len;

	len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	str = (char*)malloc(sizeof(char) * (len + 1));
	read(fd, str, (size_t)len);
	while (len > 0)
	{
		if (str[len - 1] == ' ' || str[len - 1] == '\t')
		{
			len--;
			continue;
		}
		break ;
	}
	if (str[len - 1] != '\n')
		error("No newline at the end of file.");
	return (str);
}

unsigned int		reverse_bit(unsigned int a)
{
	unsigned int	b;
	int				i;

	i = 0;
	b = 0;
	while (i < 3)
	{
		if (i)
			a = a >> 8;
		b = b | (a & 255);
		b = b << 8;
		i++;
	}
	a = a >> 8;
	b = b | (a & 255);
	return (b);
}

t_header			*new_head(void)
{
	t_header		*ret;

	ret = (t_header*)malloc(sizeof(t_header));
	ft_bzero(ret->prog_name, sizeof(char) * (PROG_NAME_LENGTH + 1));
	ft_bzero(ret->comment, sizeof(char) * (COMMENT_LENGTH + 1));
	ret->prog_size = 0;
	ret->magic = reverse_bit(COREWAR_EXEC_MAGIC);
	return (ret);
}

char				*get_name(char *str)
{
	char			*ret;
	int				i;
	int				j;

	j = 0;
	i = 0;
	while (*str != '\"')
		str++;
	str++;
	while (str[i] != '\"')
		i++;
	ret = (char*)malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
