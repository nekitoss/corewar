/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:44:44 by rhulam            #+#    #+#             */
/*   Updated: 2016/12/01 15:46:49 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget_node(t_list *start, size_t pos)
{
	size_t i;

	if (start)
	{
		i = 0;
		while (i != pos && start)
		{
			i++;
			start = start->next;
		}
	}
	return (start);
}
