/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:52 by rhulam            #+#    #+#             */
/*   Updated: 2016/11/29 13:49:42 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_temp;
	t_list	*new_list;
	t_list	*temp1;
	t_list	*temp2;

	temp1 = lst;
	new_list = (t_list*)malloc(sizeof(t_list));
	new_temp = new_list;
	while (temp1)
	{
		temp2 = f((t_list*)temp1);
		new_temp->content = temp2->content;
		new_temp->content_size = temp2->content_size;
		if (temp1->next == NULL)
			break ;
		new_temp->next = (t_list*)malloc(sizeof(t_list));
		new_temp = new_temp->next;
		new_temp->next = NULL;
		temp1 = temp1->next;
	}
	return (new_list);
}
