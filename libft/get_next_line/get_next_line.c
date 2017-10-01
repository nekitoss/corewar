/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 13:48:29 by rhulam            #+#    #+#             */
/*   Updated: 2017/01/08 17:04:23 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_rhulam	*push_back(t_rhulam **start, t_rhulam *new_node)
{
	t_rhulam		*node_start;

	if (start)
	{
		if (*start)
		{
			node_start = *start;
			while (node_start->next)
				node_start = node_start->next;
			node_start->next = new_node;
		}
		else
			*start = new_node;
	}
	return (new_node);
}

t_rhulam	*lstnew(int fd)
{
	t_rhulam		*link;

	if (!(link = (t_rhulam *)malloc(sizeof(t_rhulam))))
		return (NULL);
	link->fd = fd;
	link->pos = 0;
	link->s[0] = '\0';
	link->next = NULL;
	return (link);
}

int			reading(t_rhulam *list, int fd, char **line, int *count)
{
	int				ret;

	while (1)
	{
		if (list->pos == BUFF_SIZE || list->s[0] == '\0')
		{
			ret = read(fd, list->s, BUFF_SIZE);
			list->s[ret] = '\0';
			list->pos = 0;
			if (!ret)
				break ;
		}
		ft_memmove(list->s, (list->s) + list->pos, BUFF_SIZE - list->pos);
		if (list->s[0] == '\0')
		{
			if ((ret = read(fd, list->s, BUFF_SIZE)) == 0)
				return (0);
			list->s[ret] = '\0';
			list->pos = 0;
		}
		list->s[BUFF_SIZE - list->pos] = '\0';
		if (reading2(list, count, line))
			break ;
	}
	return (*count);
}

int			reading2(t_rhulam *list, int *count, char **line)
{
	int				i;
	char			str[BUFF_SIZE + 1];

	list->pos = 0;
	i = 0;
	while (list->s[i] != '\0')
	{
		if (list->s[i] == '\n')
			break ;
		i++;
	}
	*count = 1;
	if (list->s[i] != '\0')
	{
		ft_strcpy(str, list->s);
		str[i] = '\0';
		*line = ft_strjoin(*line, str);
		list->pos += i + 1;
		return (1);
	}
	*line = ft_strjoin(*line, list->s);
	list->pos = BUFF_SIZE;
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_rhulam	*first = NULL;
	t_rhulam		*list;
	int				count;

	count = 0;
	if (fd == -1 || read(fd, NULL, 0) == -1 || fd == 1)
		return (-1);
	*line = ft_strnew(0);
	if (!first)
	{
		first = lstnew(fd);
		list = first;
	}
	else
	{
		list = first;
		while (list && list->fd != fd)
			list = list->next;
		if (!list)
			list = push_back(&first, lstnew(fd));
	}
	return (reading(list, fd, line, &count));
}
