/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:08:58 by yrobotko          #+#    #+#             */
/*   Updated: 2016/12/13 19:12:21 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *tmp;

	if (!alst)
		return ;
	while ((*alst)->next)
	{
		tmp = (*alst)->next;
		(*del)((void*)(*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = 0;
		*alst = tmp;
	}
	(*del)((void*)(*alst)->content, (*alst)->content_size);
	ft_memdel((void*)alst);
}
