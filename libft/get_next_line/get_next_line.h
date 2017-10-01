/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 13:48:50 by rhulam            #+#    #+#             */
/*   Updated: 2017/01/08 15:42:22 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft.h"

# define BUFF_SIZE 1024

typedef struct		s_rhulam
{
	char			s[BUFF_SIZE + 1];
	int				fd;
	int				pos;
	struct s_rhulam	*next;
}					t_rhulam;

int					get_next_line(const int fd, char **line);
t_rhulam			*push_back(t_rhulam **start, t_rhulam *new_node);
t_rhulam			*lstnew(int fd);
int					reading(t_rhulam *list, int fd, char **line, int *count);
int					reading2(t_rhulam *list, int *count, char **line);

#endif
