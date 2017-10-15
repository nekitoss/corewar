/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 18:09:37 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/16 18:17:00 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list *list, void *data, size_t size)
{
	t_list *lst;

	if (!list || !data)
		return ;
	while (list)
		list = list->next;
	if (!(lst = (t_list*)malloc(sizeof(t_list))))
		return ;
	lst->content = data;
	lst->content_size = size;
	lst->next = 0;
	list->next = lst;
}
