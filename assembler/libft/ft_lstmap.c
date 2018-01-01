/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:58:28 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/13 16:20:13 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*prev;
	t_list	*new;
	t_list	*begin;

	if (!lst || !f)
		return (0);
	new = f(lst);
	begin = new;
	prev = new;
	while (lst->next)
	{
		lst = lst->next;
		new = f(lst);
		prev->next = new;
		prev = new;
	}
	new->next = 0;
	return (begin);
}
