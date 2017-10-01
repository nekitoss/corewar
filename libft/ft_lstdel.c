/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhulam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:58:58 by rhulam            #+#    #+#             */
/*   Updated: 2016/11/29 13:33:56 by rhulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp1;
	t_list *temp2;

	temp1 = *alst;
	temp2 = NULL;
	while (temp1 != NULL)
	{
		del(temp1->content, temp1->content_size);
		temp2 = temp1->next;
		free(temp1);
		temp1 = temp2;
	}
	*alst = NULL;
}
