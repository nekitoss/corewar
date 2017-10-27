/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:49:45 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/16 16:31:45 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	void	*data;
	t_list	*newlst;

	if (!(newlst = (t_list*)malloc(sizeof(t_list))))
		return (0);
	if (!content || content_size == 0)
	{
		newlst->content = 0;
		newlst->content_size = 0;
		newlst->next = 0;
	}
	else
	{
		data = (void*)malloc(sizeof(void) * content_size);
		if (data)
		{
			ft_memmove(data, content, content_size);
			newlst->content = data;
			newlst->content_size = content_size;
			newlst->next = 0;
		}
	}
	return (newlst);
}
