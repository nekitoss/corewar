/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 17:21:20 by yrobotko          #+#    #+#             */
/*   Updated: 2017/02/07 15:15:37 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"

static t_gnl		*createlist(int fd)
{
	t_gnl	*list;

	list = (t_gnl*)malloc(sizeof(t_gnl));
	list->buff = ft_strnew(BUFF_SIZE);
	list->fdiscriptor = fd;
	list->next = 0;
	return (list);
}

static char			*get_buff(int fd)
{
	static t_gnl	*head_of_list = 0;
	t_gnl			*ptr;

	ptr = head_of_list;
	if (!head_of_list)
	{
		head_of_list = createlist(fd);
		return (head_of_list->buff);
	}
	while (ptr->next)
	{
		if (ptr->fdiscriptor == fd)
			return (ptr->buff);
		ptr = ptr->next;
	}
	if (ptr->fdiscriptor == fd)
		return (ptr->buff);
	ptr->next = createlist(fd);
	ptr = ptr->next;
	return (ptr->buff);
}

static int			fill_from_buff(char *buff, char **tmp_line)
{
	char	*ptr_n;
	char	*str_before_n;
	char	*to_free;

	to_free = *tmp_line;
	ptr_n = ft_strchr(buff, '\n');
	if (!ptr_n)
	{
		*tmp_line = ft_strjoin(*tmp_line, buff);
		ft_strclr(buff);
		free(to_free);
		return (0);
	}
	str_before_n = ft_strnew(ptr_n - buff);
	ft_strncpy(str_before_n, buff, ptr_n - buff);
	ft_strcpy(buff, ptr_n + 1);
	*tmp_line = ft_strjoin(*tmp_line, str_before_n);
	free(to_free);
	free(str_before_n);
	return (1);
}

int					get_next_line(const	int fd, char **line)
{
	char	*buff;
	char	*ret_str;
	size_t	count;

	buff = get_buff(fd);
	if (read(fd, buff, 0) == -1 || !buff || !line)
		return (-1);
	ret_str = ft_strnew(0);
	while (1)
	{
		if (fill_from_buff(buff, &ret_str))
			break ;
		else if ((count = read(fd, buff, BUFF_SIZE)) == 0)
		{
			if (!*ret_str)
				return (0);
			else
				break ;
		}
		buff[count] = 0;
	}
	*line = ret_str;
	return (1);
}
